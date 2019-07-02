function Main_Function(phase,x,y)
%   This is the main function here on matlab, this is responsible for
%   opening, sending the message and closing the serial port, making calls
%   for Check_Workspace and Two_Link_Inverse_Kinematics.
%   It's necessary to give which phase is going on and the point P(x,y) desired
    clc
    
    s = serial('COM15');
    %fopen(s);
    
    L1 = 1;
    L2 = 1;
   
    if ~Check_Workspace(x,y,L1,L2)
        disp(strcat('Ponto (',num2str(x),',',num2str(y), ') fora da area de trabalho'))
        return;
    end
   
    arival_time = '4';
    speed1 = '1';
    speed2 = '1';    
        
    [teta1,teta2] = Two_Link_Inverse_Kinematics(x,y,L1,L2);
    
    teta1 = num2str(teta1);
    teta2 = num2str(teta2);
    x = num2str(x);
    y = num2str(y);
    
    if phase > 4
        disp('Fase não implementada')
        return;
    elseif phase == 4
        str = strcat('(4,',x,',',y,',',teta1,',',teta2,',',speed1,')');
    elseif phase == 0
        str = '(0)';
    elseif phase == 1
        str = strcat('(1,',teta1,',',speed1,',',teta2,',',speed2,')'); 
    elseif phase == 2
        str = strcat('(2,',teta1,',',teta2,',',speed1,')'); 
    elseif phase == 3
        str = strcat('(3,',teta1,',',teta2,',',arival_time,')'); 
        
    end
    %disp(str)
    fprintf(s,str);
    fclose(s);
end

