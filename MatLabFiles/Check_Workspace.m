function [Response] = Check_Workspace(x,y,L1,L2)
%   Given a bilinear robot with L1 and L2 as links size, respond if
%   the point (x,y) is inside reachable workspace for that robot.
%   The point is inside workspace if Response = 1, else is not.

    teta0 = deg2rad(17.77);
    teta1 = deg2rad(13.52);

    if sqrt(x^2 + y^2) > (L1+L2)
        Response = 0;
    elseif (x >= 0) && atan(y/x) < teta1
        Response = 0;
    elseif (x < 0) && (atan(y/abs(x))) < teta0
        Response = 0;
    elseif sqrt((x-(-L1*cos(teta0)))^2 + (y-(L1*sin(teta0)))^2) < L2
        Response = 0;
    else
        Response = 1;
    end    
end