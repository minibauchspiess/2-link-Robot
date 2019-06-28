function [Teta1,Teta2] = Two_Link_Inverse_Kinematics(x,y,link1,link2)
    clc
    
    n = (x^2 + y^2 - link1^2 - link2^2)/(2*link1*link2);
    Teta2 = -acos(n);
    
    m = y*(link1 + link2*cos(Teta2)) - x*link2*sin(Teta2);
    m = m/(x*(link1 + link2*cos(Teta2)) + y*link2*(Teta2));
    Teta1 = rad2deg(atan(m));
    Teta2 = rad2deg(Teta2);
end