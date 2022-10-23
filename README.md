[![View pointPolygonTest on File Exchange](https://www.mathworks.com/matlabcentral/images/matlab-file-exchange.svg)](https://ww2.mathworks.cn/matlabcentral/fileexchange/119418-pointpolygontest)

# Points In Polygon Test

This function [`inpolygon2`](./inpolygon2.m) is an enhancement of matlab's built-in function [`inpolygon`](https://www.mathworks.cn/help/matlab/ref/inpolygon.html), which supports the calculation of the distances.Support C/C++ code generation.

## Example

```matlab
%% data, is same as https://www.mathworks.cn/help/matlab/ref/inpolygon.html fisrst Example
L = linspace(0,2*pi,6);
xv = cos(L)';
yv = sin(L)';

rng default
xq = randn(250,1);
yq = randn(250,1);

%% use inpolygon2 function determine points whether inside polygon 
points = [xq,yq];
dists = inpolygon2([xv,yv],points);

figure;hold on
plot(xv,yv) % polygon
plot(xq(dists==1),yq(dists==1),'r+') % points inside
plot(xq(dists==-1),yq(dists==-1),'bo') % points outside
axis equal;
title("points in polygon")
```

![img](a.png)

```matlab
%% Distance Rating Heat Map
xy=-2:.02:2;
[x,y] = meshgrid(xy);
points = [x(:),y(:)];
dists2 = inpolygon2([xv,yv],points,true);
dists2 = reshape(dists2,size(x));

figure;hold on;
xydata = [xy(1),xy(end)];
imagesc(xydata,xydata,dists2)
plot(xv,yv,'w-','LineWidth',2)
colormap('jet');
colorbar
axis equal off
title("signed distance hot map")
```

![img](b.png)
