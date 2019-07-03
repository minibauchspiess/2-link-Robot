function [Teta1,Teta2] = Two_Link_Inverse_Kinematics(x,y,L1,L2)
%   Calculates the inverse Kinematics for a planar robot with 2 links given
%   (x,y) desired and both links lenths 
    n = (x^2 + y^2 - L1^2 - L2^2)/(2*L1*L2);
    Teta2 = -acos(n);
    
    m = y*(L1 + L2*cos(Teta2)) - x*L2*sin(Teta2);
    m = m/(x*(L1 + L2*cos(Teta2)) + y*L2*sin(Teta2));
    Theta1 = atan(m);
    if Theta1 < 0
        Theta1 = Theta1 + pi;
    end
    Teta1 = num2str(rad2deg(Theta1));
    Teta2 = num2str(rad2deg(Teta2));
end