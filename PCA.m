clear all

%R^2 value using raw data 
B0 = xlsread('PCA.xlsx',1,'B2:B12');
X = xlsread('PCA.xlsx',1,'C2:AH12');
Y = xlsread('PCA.xlsx',1,'AI2:AI12');
y_bar = mean(Y);

%standardising the data
x_bar = mean(X,1);
sd = std(X);                           %std dev using n-1 (sample)
xb_mat = repmat(x_bar,11,1);
sd_mat = repmat(sd,11,1);
num_std = X-xb_mat ;
x_std = ((num_std)./sd_mat);      % standardization of variables
y_std = Y-y_bar;
y_barstd = mean(y_std);           %for calc r^2 value of transformed data

%covariance matrix
CV = round((cov(x_std)),2);        %covariance matrix %round off to 2 decimals

%eigen values and eigen vectors
[V,G] = eig(CV);                %V - eigen vector; G - eigen values
EV = diag(G);

%percentage variance explained
Trace = sum(EV,1);
pct_1 = ((EV(1,1))/Trace)*100;
pct_2 = ((EV(2,1))/Trace)*100;
pct_3 = ((EV(3,1))/Trace)*100;
pct_4 = ((EV(4,1))/Trace)*100;
pct_5 = ((EV(5,1))/Trace)*100;
pct_6 = ((EV(6,1))/Trace)*100;
pct_7 = ((EV(7,1))/Trace)*100;
pct_8 = ((EV(8,1))/Trace)*100;
pct_9 = ((EV(9,1))/Trace)*100;
pct_10 = ((EV(10,1))/Trace)*100;
pct_11 = ((EV(11,1))/Trace)*100;
pct_12 = ((EV(12,1))/Trace)*100;
pct_13 = ((EV(13,1))/Trace)*100;
pct_14 = ((EV(14,1))/Trace)*100;
pct_15 = ((EV(15,1))/Trace)*100;
pct_16 = ((EV(16,1))/Trace)*100;
pct_17 = ((EV(17,1))/Trace)*100;
pct_8 = ((EV(18,1))/Trace)*100;
pct_19 = ((EV(19,1))/Trace)*100;
pct_20 = ((EV(20,1))/Trace)*100;
pct_21 = ((EV(21,1))/Trace)*100;
pct_22 = ((EV(22,1))/Trace)*100;
pct_23 = ((EV(23,1))/Trace)*100;
pct_24 = ((EV(24,1))/Trace)*100;
pct_25 = ((EV(25,1))/Trace)*100;
pct_26 = ((EV(26,1))/Trace)*100;
pct_27 = ((EV(27,1))/Trace)*100;
pct_28 = ((EV(28,1))/Trace)*100;
pct_29 = ((EV(29,1))/Trace)*100;
pct_30 = ((EV(30,1))/Trace)*100;
pct_31 = ((EV(31,1))/Trace)*100;
pct_32 = ((EV(32,1))/Trace)*100;

% feature vector
V_1 = V(:,5:10);           %selected PCs %change this 

%Transformed matrix 
Z = x_std*V_1;

%regression using transformed data
B_t = (inv(Z'*Z))*(Z'*y_std);    %B matrix calculation
n_t = size(x_std,1);
Rsqu_t = ((B_t'*Z'*y_std)-(n_t*(y_barstd)^2))/((y_std'*y_std)-(n_t*(y_barstd)^2));
