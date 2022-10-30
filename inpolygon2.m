function dists = inpolygon2(contour,points,meatureDist)%#codegen
% Brief: determine `points` are inside, on or outside a polygon/contour or 
% calculate signed distance between `points` and the nearest contour edge.
% Details:
%    This function determines whether points are inside a contour, outside, or
% lies on an edge (or coincides with a vertex). It returns positive (inside),
% negative (outside), or zero (on an edge) value, correspondingly. When
% measureDist=false , the return value is +1, -1, and 0, respectively.
% Otherwise, the return value is a signed distance between the point and
% the nearest contour edge.
% 
% Principle: 
%    The number of points of intersection between a ray passing 
% through a point and a contour, if even, outside the polygon, otherwise 
% inside the polygon.(this function is equivalent to the OpenCV function 
% `pointPolygonTest`)
%
% Note:
%    This function is an enhancement of matlab's built-in function `inpolygon`,
% which supports the calculation of the distances.
%
% Syntax:
%     dists = inpolygon2(contour,points,meatureDist)
%
% Inputs:
%    contour - [n,2] size,[double] type,Polygonal order vertices.
%    points - [m,2] size,[double] type,Coordinate points of the query.
%    meatureDist - [1,1] size,[logical] type,Whether meature distances.
%
% Outputs:
%    dists - [m,1] size,[double] type,Description
%
% Example 1:
%       % Self-intersecting polygon
%       xv = rand(6,1); yv = rand(6,1);
%       xv = [xv ; xv(1)]; yv = [yv ; yv(1)];
%       x = rand(1000,1); y = rand(1000,1);
%       dists = inpolygon2([xv,yv],[x,y]);
%       in = dists==1; % in:1,on:0,out:-1
%       plot(xv,yv,x(in),y(in),'.r',x(~in),y(~in),'.b')
%
% Example 2:
%       % Self-intersecting polygon, calucate point nearst distance
%       xv = 2*rand(6,1)-1; yv = 2*rand(6,1)-1;
%       xv = [xv ; xv(1)]; yv = [yv ; yv(1)];
%       xy=-2:.01:2;
%       [x,y] = meshgrid(xy);
%       points = [x(:),y(:)];
%       dists = inpolygon2([xv,yv],points,true);
%
%       figure;hold on;
%       dists = reshape(dists,size(x));
%       xydata = [xy(1),xy(end)];
%       imagesc(xydata,xydata,dists)
%       plot(xv,yv,'w-')
%       colormap('jet');
%       colorbar
%       axis equal off
%       title("distance hot map")
%
%   Class support for inputs contour,points:
%      float: double, single
%
% See also: inpolygon

% Author:                          cuixingxing
% Email:                           cuixingxing150@gmail.com
% Created:                         22-Oct-2022 15:33:44
% Version history revision notes:
%                                  None
% Implementation In Matlab R2022b
% Copyright © 2022 TheMatrix.All Rights Reserved.
%

arguments
    contour (:,2) {mustBeNumeric}
    points (:,2) {mustBeNumeric}
    meatureDist (1,1) logical = false
end

assert(size(contour,1)>=3,"contour at least 3 vertices");

% close loop polygon
range= max(contour(:))-min(contour(:));
if any(contour(1,:)-contour(end,:)>3*eps(range))
    contour = [contour;contour(1,:)];
end
N = size(contour,1)-1;
M = size(points,1);

% pre-allocation
counts = zeros(M,1);
dists = inf(M,1);
maxDists = inf(M,1);
minDist = inf(M,1);
currDist = inf(M,1);
preIdxs = zeros(M,1,'logical');
idxs = (1:M)';
p_idxs = idxs;
for i = 1:N
    v1 = contour(i,:);
    v2 = contour(i+1,:);

    % on line
    % 点p位于线段v1v2之间，满足向量v1p和pv2方向向量相同，即满足公式(p.y-v1.y)*(v2.x-p.x)==(v2.y-p.y)*(p.x-v1.x)
    isOnLine = all(points-v1==0,2)|all(points-v2==0,2)|....
        all((points(:,2)-v1(2)).*(v2(1)-points(:,1))==(v2(2)-points(:,2)).*(points(:,1)-v1(1)),2);% point 位于线段v1v2之间
    dists(isOnLine) = 0;
    onLineIdxs = preIdxs|isOnLine;
    preIdxs = onLineIdxs;
    p = points(~onLineIdxs,:);
    p_idxs = idxs(~onLineIdxs);

    if ~isempty(p)
        % determine in or out
        vMid = 0.5*(contour(1,:)+contour(2,:));
        l1 = v1-p;
        l2 = v2-p;
        l3 = vMid-p;

        l1l2Orientation = sign(l1(:,1).*l2(:,2)-l2(:,1).*l1(:,2));% 外积判断方向
        l1l3Orientation = sign(l1(:,1).*l3(:,2)-l3(:,1).*l1(:,2));
        l3l2Orientation = sign(l3(:,1).*l2(:,2)-l2(:,1).*l3(:,2));
        isInRange = (l1l2Orientation-l1l3Orientation==0)&(l1l3Orientation-l3l2Orientation==0);% 射线位于pv1,pv2夹角之间
        idxs1 = p_idxs(isInRange&l1l2Orientation==0);%l1l2Orientation==0 为射线与边界线重合
        idxs2 = p_idxs(isInRange&l1l2Orientation~=0);
        counts(idxs1) = counts(idxs1)+2;
        counts(idxs2) = counts(idxs2)+1;

        % calculate dist
        if meatureDist
            lnorm = zeros(numel(l1l2Orientation),2);
            cond = l1l2Orientation<0;
            lnorm(cond,:) = repmat([v1(2)-v2(2),v2(1)-v1(1)],sum(cond),1);% 向量v1v2的法式量，方向位于pv1，pv2的夹角方向之间
            lnorm(~cond,:) = repmat(-[v1(2)-v2(2),v2(1)-v1(1)],sum(~cond),1);

            l1lnorm = sign(l1(:,1).*lnorm(:,2)-lnorm(:,1).*l1(:,2));
            lnorml2 = sign(lnorm(:,1).*l2(:,2)-l2(:,1).*lnorm(:,2));

            idx3 = l1l2Orientation-l1lnorm==0 & l1lnorm-lnorml2==0 & l1l2Orientation~=0;
            p_idx3 = p_idxs(idx3);
            p_idx4 = p_idxs(~idx3);
            pp3 = p(idx3,:);
            pp4 = p(~idx3,:);
            % 平面中经过点v1(x1,y1),v2(x2,y2)的标准直线方程为：(y1-y2)*x+(x2-x1)*y+x1*y2-x2*y1==0
            % 点p(x0,y0)到直线l:a*x+b*y+c==0的距离公式为：d =
            % abs(a*x0+b*y0+c)/sqrt(a^2+b^2)
            a = v1(2)-v2(2);
            b = v2(1)-v1(1);
            c = v1(1)*v2(2)-v2(1)*v1(2);
            x0 = pp3(:,1);
            y0 = pp3(:,2);
            currDist(p_idx3) = abs(a.*x0+b.*y0+c)./sqrt(a^2+b^2);

            d1 = sqrt((pp4(:,1)-v1(1)).^2+(pp4(:,2)-v1(2)).^2);
            d2 = sqrt((pp4(:,1)-v2(1)).^2+(pp4(:,2)-v2(2)).^2);
            currDist(p_idx4) = min(d1,d2);

            minDist(p_idxs) = min(currDist(p_idxs),maxDists(p_idxs));
            maxDists(p_idxs) = minDist(p_idxs);
        end
    end
end

idxC =  logical(mod(counts(p_idxs),2));
dists(p_idxs(idxC)) = 1;
dists(p_idxs(~idxC)) = -1;

if meatureDist
    dists(p_idxs) = dists(p_idxs).*minDist(p_idxs);
end

