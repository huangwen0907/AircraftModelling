function [states_OUT, cov_OUT,nu,S_OUT] = simulateEKF(accelerations,omega,ALP,BET,u,Vt,H)
persistent states cov prev_p prev_q prev_r 

%Intialise filter
if isempty(states)
    states = zeros(19,1);
    cov = zeros(19,19);
    
    states(1,1)  = accelerations(1);    cov(1,1)   = 1e-5^2; % Body Acceleration X
    states(2,1)  = accelerations(2);    cov(2,2)   = 1e-5^2; % Body Acceleration Y
    states(3,1)  = accelerations(3);    cov(3,3)   = 1e-5^2; % Body Acceleration Z
    
    states(4,1)  = omega(1);    cov(4,4)   = 1e-5^2; % P
    states(5,1)  = omega(2);    cov(5,5)   = 1e-5^2; % Q
    states(6,1)  = omega(3);    cov(6,6)   = 1e-5^2; % R
    
    states(7,1)  = 1;           cov(7,7)   = 1e-3^2;
    states(8,1)  = 1;           cov(8,8)   = 1e-3^2;
    
    states(9,1)  = 1;           cov(9,9)   = 1e-3^2;
    states(10,1) = 1;           cov(10,10) = 1e-3^2;
    states(11,1) = 1;           cov(11,11) = 1e-3^2;
    
    states(12,1) = 1;           cov(12,12) = 1e-3^2;
    states(13,1) = 1;           cov(13,13) = 1e-3^2;
    states(14,1) = 1;           cov(14,14) = 1e-3^2;
    
    states(15,1) = 1;           cov(15,15) = 1e-3^2;
    states(16,1) = 1;           cov(16,16) = 1e-3^2;
    states(17,1) = 1;           cov(17,17) = 1e-3^2;
    states(18,1) = 1;           cov(18,18) = 1e-3^2;
    states(19,1) = 1;           cov(19,19) = 1e-3^2;
        
    prev_p = 0;
    prev_q = 0;
    prev_r = 0;
    
%     cov = cov.^2;
end

%Define filter parameters:
Q = (eye(19,19)*1e-3).^2;
R = (eye(6,6)*1e-5).^2;
F = eye(19);
R2D = 180/pi;

%***Constants***
g   = 9.81;
vs  = 340.3;
R2D = 180/pi;
rho = 1.225;%1.225*(1-H/44.331/1000)^4.256;
dt  = 0.005; 
m   = 38924 * 0.453592 / 15;

%***Extract states***
deltaA      = u(1);
deltaE      = u(2);
deltaR      = u(3);
throttle    = u(4);
dE          = deltaE*R2D;
dA          = deltaA*R2D;
dR          = deltaR*R2D;

p      = states(4,1);
q      = states(5,1);
r      = states(6,1);

states(7:end) = 1; 

CX_dE  = states(7,1); 

CY_dR  = states(8,1);
CY_dE  = states(9,1);

CZ_dE  = states(10,1); 
CZ_dA  = states(11,1);

Cl_dA  = states(12,1);
Cl_dR  = states(13,1);
Cl_dE  = states(14,1); 

Cm_dE  = states(15,1); 
Cm_dA  = states(16,1);

Cn_dA  = states(17,1);
Cn_dR  = states(18,1); 
Cn_dE  = states(19,1);

CX_dE1 = CX_dE*9.5e-4; 
CX_dE2 = CX_dE*8.5e-7; 

CY_dR1 = CY_dR*1.55e-3;
CY_dR2 = CY_dR*8e-6;
CY_dE1 = CY_dE*1.75e-4;

CZ_dE1 = CZ_dE*4.76e-3; 
CZ_dE2 = CZ_dE*3.3e-5; 
CZ_dA1 = CZ_dA*7.5e-5;

Cl_dA1 = Cl_dA*6.1e-4;
Cl_dA2 = Cl_dA*2.5e-5;
Cl_dA3 = Cl_dA*2.6e-6;
Cl_dR1 = Cl_dR*-2.3e-4;
Cl_dR2 = Cl_dR*4.5e-6;
Cl_dE1 = Cl_dE*5.24e-5; 

Cm_dE1 = Cm_dE*6.54e-3; 
Cm_dE2 = Cm_dE*8.49e-5; 
Cm_dE3 = Cm_dE*3.74e-6;
Cm_dA1 = Cm_dA*3.5e-5;

Cn_dA1 = Cn_dA*1.4e-5;
Cn_dA2 = Cn_dA*7.0e-6;
Cn_dR1 = Cn_dR*9.0e-4; 
Cn_dR2 = Cn_dR*4.0e-6; 
Cn_dE1 = Cn_dE*8.73e-5;
Cn_dE2 = Cn_dE*8.7e-6;

%Predict
S       = 20;
m       = 38924 * 0.453592 / 15;%1905;
b       = 20/3;
cbar    = 3;
Ix      = 24970*14.593903*0.092903/15;
Iy      = 122190*14.593903*0.092903/15;
Iz      = 139800*14.593903*0.092903/15;
Ixz     = 1175*14.593903*0.092903/15;
xCG_ref = 0;
xCG     = 0;

%***Calculate Dynamic Pressure***
qbar = 0.5*rho*Vt^2;

%***Calculate dimensional values***
hT = H/3048;

Tmax = ((30.21-0.668*hT-6.877*hT^2+1.951*hT^3-0.1512*hT^4) + ...
    (Vt/vs).*(-33.8+3.347*hT+18.13*hT^2-5.865*hT^3+0.4757*hT^4) + ...
    (Vt/vs)^2.*(100.8-77.56*hT+5.441*hT^2+2.864*hT^3-0.3355*hT^4) + ...
    (Vt/vs)^3.*(-78.99+101.4*hT-30.28*hT^2+3.236*hT^3-0.1089*hT^4) + ...
    (Vt/vs)^4.*(18.74-31.6*hT+12.04*hT^2-1.785*hT^3+0.09417*hT^4))*4448.22/20; % Newton's

T = Tmax*throttle;

CX = -0.0434 + 2.39e-3*ALP+2.53e-5*BET^2-1.07e-6*ALP*BET^2+CX_dE1*dE-CX_dE2*dE*BET^2+(180*q*cbar/pi/2/Vt)*(8.73e-3+0.001*ALP-1.75e-4*ALP^2);
CY = -0.012*BET+CY_dR1*dR-CY_dR2*dR*ALP+(180*b/pi/2/Vt)*(2.25e-3*p+0.0117*r-3.67e-4*r*ALP+CY_dE1*r.*dE);
CZ = -0.131-0.0538*ALP-CZ_dE1*dE-CZ_dE2*dE*ALP-CZ_dA1*dA.^2+(180*q*cbar/pi/2/Vt).*(-0.111+5.17e-3*ALP-1.1e-3*ALP^2);
Cl = -5.98e-4*BET-2.83e-4*ALP*BET+1.51e-5*ALP^2*BET-dA.*(Cl_dA1+Cl_dA2*ALP-Cl_dA3*ALP^2)-dR.*(Cl_dR1+Cl_dR2*ALP)+(180*b/2/pi/Vt).*(-4.12e-3*p-5.24e-4*p*ALP+4.36e-5*p*ALP^2+4.36e-4*r+1.05e-4*r*ALP+Cl_dE1*r.*dE);
Cm = -6.61e-3-2.67e-3*ALP-6.48e-5*BET^2-2.65e-6*ALP*BET^2-Cm_dE1*dE-Cm_dE2*dE*ALP+Cm_dE3*dE*BET^2-Cm_dA1*dA.^2+(180*q*cbar/2/pi/Vt).*(-0.0473-1.57e-3*ALP)+(xCG_ref-xCG)*CZ;
Cn = 2.28e-3*BET+1.79e-6*BET^3+Cn_dA1*dA+Cn_dA2*dA*ALP-Cn_dR1*dR+Cn_dR2*dR*ALP+(180*b/2/pi/Vt).*(-6.63e-5*p-1.92e-5*p*ALP+5.06e-6*p*ALP^2-6.06e-3*r-Cn_dE1*r.*dE+Cn_dE2*r.*dE*ALP)-cbar/b*(xCG_ref-xCG)*CY;

c1 = ((Iy-Iz)*Iz-Ixz^2)/(Ix*Iz-Ixz^2);
c2 = (Ix-Iy+Iz)*Ixz/(Ix*Iz-Ixz^2);
c3 = Iz/(Ix*Iz-Ixz^2);
c4 = Ixz/(Ix*Iz-Ixz^2);
c5 = (Iz-Ix)/Iy;
c6 = Ixz/Iy;
c7 = 1/Iy;
c8 = ((Ix-Iy)*Ix-Ixz^2)/(Ix*Iz-Ixz^2);
c9 = Ix/(Ix*Iz-Ixz^2);

heng = 0;
pdot = (c1*r+c2*p+c4*heng)*q+qbar*S*b*(c3*Cl+c4*Cn);
qdot = (c5*p-c7*heng)*r-c6*(p^2-r^2)+qbar*S*cbar*c7*Cm;
rdot = (c8*p-c2*r+c9*heng)*q+qbar*S*b*(c4*Cl+c9*Cn);

%***Predict States***
states(1,1) = (qbar*S*CX+T)/m; 
states(2,1) = qbar*S*CY/m; 
states(3,1) = qbar*S*CZ/m;

%Integrate
pNew = p + dt*(prev_p+pdot)/2;
qNew = q + dt*(prev_q+qdot)/2;
rNew = r + dt*(prev_r+rdot)/2;

prev_p = pNew;
prev_q = qNew;
prev_r = rNew;

states(4,1) = pNew;
states(5,1) = qNew;
states(6,1) = rNew;

F(1,1) = 0;
F(1,5) = (1.460334333819828426948389041052*qbar*(- 0.000175*ALP^2 + 0.001*ALP + 0.00873))/Vt;
F(1,7) = 0.016991761536715991584456999092618*qbar*(- 0.00000085000000000000001447545425539709*dE*BET^2 + 0.00095*dE);

F(2,2)  = 0;
F(2,4)  = (0.0073016716690991420258687569821225*qbar)/Vt;
F(2,6)  = (3.2451874084885075670527808809433*qbar*(0.000175*CY_dE*dE - 0.00036699999999999997598101875162513*ALP + 0.0117))/Vt;
F(2,8)  = 0.016991761536715991584456999092618*qbar*(0.00155*dR - 0.0000079999999999999996379848946070901*ALP*dR);
F(2,9)  = (0.00056790779648548882423423665416508*dE*qbar*r)/Vt;

F(3,3)  = 0;
F(3,5)  = -(1.460334333819828426948389041052*qbar*(0.0011*ALP^2 - 0.00517*ALP + 0.111))/Vt;
F(3,10) = -0.016991761536715991584456999092618*qbar*(0.00476*dE + 0.000033000000000000002530094189712173*ALP*dE);
F(3,11) = -0.0000012743821152536993688342749319463*dA^2*qbar;

F(4,4)  = 0.5*dt*(0.014338034095370216433606991301986*q - 133.33333333333333333333333333333*qbar*((0.084653457277151632633481163237447*(- 0.000043600000000000002685698885507293*ALP^2 + 0.00052400000000000005167394290239713*ALP + 0.00412))/Vt + (0.00071150080329508703831251117964528*(- 0.000005059999999999999834552916883057*ALP^2 + 0.000019199999999999999131163747057016*ALP + 0.000066299999999999998799744826971647))/Vt)) + 1.0;
F(4,5)  = 0.5*dt*(0.014338034095370216433606991301986*p - 0.705920992793835466727614402771*r);
F(4,6)  = -0.5*dt*(0.705920992793835466727614402771*q + 133.33333333333333333333333333333*qbar*((0.00071150080329508703831251117964528*(0.000087299999999999994249565149484482*Cn_dE*dE - 0.000008699999999999999712187691291998*ALP*Cn_dE*dE + 0.00606))/Vt - (0.084653457277151632633481163237447*(0.00010500000000000000435415592470179*ALP + 0.000052399999999999999746383427812191*Cl_dE*dE + 0.00043600000000000002685698885507293))/Vt));
F(4,12) =-0.029549631053652999392034050885059*dA*dt*qbar*(- 0.0000026000000000000000941033275608794*ALP^2 + 0.000025*ALP + 0.00061);
F(4,13) = -0.029549631053652999392034050885059*dR*dt*qbar*(0.0000045000000000000001140038584368508*ALP - 0.00023); 
F(4,14) = (0.00029572274408818303523499288634426*dE*dt*qbar*r)/Vt; 
F(4,17) = 66.666666666666666666666666666667*dt*qbar*(0.000000000052155732921951913177026719447346*dA + 0.000000000026077866460975956588513359723673*ALP*dA); 
F(4,18) = -66.666666666666666666666666666667*dt*qbar*(0.0000000033528685449826230402471313740698*dR - 0.000000000014901637977700546171215550728945*ALP*dR);
F(4,19) = -(0.047433386886339135887500745309686*dt*qbar*(0.000087299999999999994249565149484482*dE*r - 0.000008699999999999999712187691291998*ALP*dE*r))/Vt;

F(5,4)  = -0.5*dt*(0.01923234307226450609706195269662*p - 0.93976593829282265324494639495867*r);
F(5,5)  = 1.0 - (0.23344767165356548584164144954176*dt*qbar*(0.00157*ALP + 0.0473))/Vt;
F(5,6)  = 0.5*dt*(0.93976593829282265324494639495867*p + 0.01923234307226450609706195269662*r);
F(5,15) = -0.0027162870009795687031503574893065*dt*qbar*(- 0.0000037400000000000001907469408118923*dE*BET^2 + 0.00654*dE + 0.000084900000000000003675532100899659*ALP*dE);
F(5,16) = -0.000000095070045034284896281790443476841*dA^2*dt*qbar; 

F(6,4)  = -0.5*dt*(0.69609284164731566324491041086731*q + 133.33333333333333333333333333333*qbar*((0.00071150080329508703831251117964528*(- 0.000043600000000000002685698885507293*ALP^2 + 0.00052400000000000005167394290239713*ALP + 0.00412))/Vt + (0.015120148985768787881099866668956*(- 0.000005059999999999999834552916883057*ALP^2 + 0.000019199999999999999131163747057016*ALP + 0.000066299999999999998799744826971647))/Vt)); 
F(6,5)  = -0.5*dt*(0.69609284164731566324491041086731*p + 0.014338034095370216433606991301986*r);
F(6,6)  = 1.0 - 0.5*dt*(0.014338034095370216433606991301986*q + 133.33333333333333333333333333333*qbar*((0.015120148985768787881099866668956*(0.000087299999999999994249565149484482*Cn_dE*dE - 0.000008699999999999999712187691291998*ALP*Cn_dE*dE + 0.00606))/Vt - (0.00071150080329508703831251117964528*(0.00010500000000000000435415592470179*ALP + 0.000052399999999999999746383427812191*Cl_dE*dE + 0.00043600000000000002685698885507293))/Vt));
F(6,12) = -0.00024836063296167578075904676844961*dA*dt*qbar*(- 0.0000026000000000000000941033275608794*ALP^2 + 0.000025*ALP + 0.00061);
F(6,13) = -0.00024836063296167578075904676844961*dR*dt*qbar*(0.0000045000000000000001140038584368508*ALP - 0.00023);
F(6,14) = (0.000002485509472844170708475146064856*dE*dt*qbar*r)/Vt; 
F(6,17) = 66.666666666666666666666666666667*dt*qbar*(0.0000000011083648094137357012413610273008*dA + 0.00000000055418240470686785062068051365042*ALP*dA);
F(6,18) = -66.666666666666666666666666666667*dt*qbar*(0.000000071252023462311581862918541396823*dR - 0.00000000031667565983249590506057752667098*ALP*dR);
F(6,19) = -(1.0080099323845858587399911112638*dt*qbar*(0.000087299999999999994249565149484482*dE*r - 0.000008699999999999999712187691291998*ALP*dE*r))/Vt;

cov = Q + F*cov*F';

%Update
H           = eye(6,19);
S           = H * cov * H' + R;
nu          = [accelerations;omega] - H*states;
K           = cov * H' * inv(S);
states      = states + K * nu;
cov         = cov - K * S * K';

states_OUT = states;
cov_OUT = diag(cov);
S_OUT = diag(S);

