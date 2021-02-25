% Intrinsic and Extrinsic Camera Parameters
%
% This script file can be directly executed under Matlab to recover the camera intrinsic and extrinsic parameters.
% IMPORTANT: This file contains neither the structure of the calibration objects nor the image coordinates of the calibration points.
%            All those complementary variables are saved in the complete matlab data file Calib_Results.mat.
% For more information regarding the calibration model visit http://www.vision.caltech.edu/bouguetj/calib_doc/


%-- Focal length:
fc = [ 3135.499420264967284 ; 3061.982288870178309 ];

%-- Principal point:
cc = [ 1987.106229138560366 ; 1572.802815865956745 ];

%-- Skew coefficient:
alpha_c = 0.000000000000000;

%-- Distortion coefficients:
kc = [ 0.123390427571316 ; -0.566536000474585 ; 0.002489994411934 ; 0.001557101142720 ; 0.000000000000000 ];

%-- Focal length uncertainty:
fc_error = [ 11.542468341857422 ; 10.468583499107812 ];

%-- Principal point uncertainty:
cc_error = [ 15.005479477640751 ; 15.854208375993405 ];

%-- Skew coefficient uncertainty:
alpha_c_error = 0.000000000000000;

%-- Distortion coefficients uncertainty:
kc_error = [ 0.025932633869218 ; 0.146667292450873 ; 0.001995597514425 ; 0.001834350397769 ; 0.000000000000000 ];

%-- Image size:
nx = 4000;
ny = 3000;


%-- Various other variables (may be ignored if you do not use the Matlab Calibration Toolbox):
%-- Those variables are used to control which intrinsic parameters should be optimized

n_ima = 11;						% Number of calibration images
est_fc = [ 1 ; 1 ];					% Estimation indicator of the two focal variables
est_aspect_ratio = 1;				% Estimation indicator of the aspect ratio fc(2)/fc(1)
center_optim = 1;					% Estimation indicator of the principal point
est_alpha = 0;						% Estimation indicator of the skew coefficient
est_dist = [ 1 ; 1 ; 1 ; 1 ; 0 ];	% Estimation indicator of the distortion coefficients


%-- Extrinsic parameters:
%-- The rotation (omc_kk) and the translation (Tc_kk) vectors for every calibration image and their uncertainties

%-- Image #1:
omc_1 = [ 2.017269e+00 ; 1.878695e+00 ; 5.386876e-01 ];
Tc_1  = [ -2.822313e+02 ; -2.607247e+02 ; 1.090913e+03 ];
omc_error_1 = [ 4.876610e-03 ; 3.458009e-03 ; 7.561496e-03 ];
Tc_error_1  = [ 5.360283e+00 ; 5.745430e+00 ; 4.351225e+00 ];

%-- Image #2:
omc_2 = [ -1.745412e+00 ; -1.776889e+00 ; -6.549242e-01 ];
Tc_2  = [ -2.469452e+02 ; -2.668753e+02 ; 1.144227e+03 ];
omc_error_2 = [ 3.685368e-03 ; 4.866259e-03 ; 6.616474e-03 ];
Tc_error_2  = [ 5.545696e+00 ; 6.034712e+00 ; 4.893557e+00 ];

%-- Image #3:
omc_3 = [ -1.896917e+00 ; -1.957979e+00 ; 4.075061e-01 ];
Tc_3  = [ -3.410852e+02 ; -3.196093e+02 ; 1.354043e+03 ];
omc_error_3 = [ 4.812095e-03 ; 3.694286e-03 ; 7.607743e-03 ];
Tc_error_3  = [ 6.506233e+00 ; 7.060978e+00 ; 4.613148e+00 ];

%-- Image #4:
omc_4 = [ -2.188834e+00 ; -2.198555e+00 ; -6.614319e-02 ];
Tc_4  = [ -3.127867e+02 ; -3.262872e+02 ; 1.105880e+03 ];
omc_error_4 = [ 4.547440e-03 ; 4.520800e-03 ; 9.631480e-03 ];
Tc_error_4  = [ 5.389345e+00 ; 5.833737e+00 ; 4.685803e+00 ];

%-- Image #5:
omc_5 = [ -2.028146e+00 ; -1.765260e+00 ; 9.579625e-01 ];
Tc_5  = [ -3.549215e+02 ; -2.256648e+02 ; 1.375503e+03 ];
omc_error_5 = [ 5.507686e-03 ; 2.970286e-03 ; 7.166500e-03 ];
Tc_error_5  = [ 6.616700e+00 ; 7.223631e+00 ; 3.883580e+00 ];

%-- Image #6:
omc_6 = [ 1.940376e+00 ; 1.970217e+00 ; 2.946826e-01 ];
Tc_6  = [ -2.526495e+02 ; -3.907182e+02 ; 1.145633e+03 ];
omc_error_6 = [ 4.420760e-03 ; 4.094255e-03 ; 7.848574e-03 ];
Tc_error_6  = [ 5.643704e+00 ; 5.984123e+00 ; 4.585866e+00 ];

%-- Image #7:
omc_7 = [ 2.071504e+00 ; 1.673444e+00 ; 1.116975e+00 ];
Tc_7  = [ -1.974683e+02 ; -1.780696e+02 ; 7.394328e+02 ];
omc_error_7 = [ 5.501327e-03 ; 2.793724e-03 ; 6.819292e-03 ];
Tc_error_7  = [ 3.661416e+00 ; 3.910756e+00 ; 3.397000e+00 ];

%-- Image #8:
omc_8 = [ 2.159561e+00 ; 2.099907e+00 ; 2.982355e-01 ];
Tc_8  = [ -2.534421e+02 ; -3.427818e+02 ; 1.048980e+03 ];
omc_error_8 = [ 4.785953e-03 ; 4.137437e-03 ; 8.870752e-03 ];
Tc_error_8  = [ 5.177286e+00 ; 5.509903e+00 ; 4.344668e+00 ];

%-- Image #9:
omc_9 = [ -1.572149e+00 ; -1.414347e+00 ; -2.805904e-01 ];
Tc_9  = [ -3.371525e+02 ; -2.478050e+02 ; 1.142940e+03 ];
omc_error_9 = [ 4.390822e-03 ; 4.282455e-03 ; 5.399549e-03 ];
Tc_error_9  = [ 5.489965e+00 ; 5.990642e+00 ; 4.423339e+00 ];

%-- Image #10:
omc_10 = [ 1.681509e+00 ; 2.068532e+00 ; 1.342169e+00 ];
Tc_10  = [ -3.016152e+00 ; -2.060960e+02 ; 8.001830e+02 ];
omc_error_10 = [ 5.558369e-03 ; 3.469638e-03 ; 7.154545e-03 ];
Tc_error_10  = [ 3.880543e+00 ; 4.182538e+00 ; 3.757317e+00 ];

%-- Image #11:
omc_11 = [ 1.934441e+00 ; 1.836040e+00 ; 7.634901e-01 ];
Tc_11  = [ -1.451702e+02 ; -3.303809e+02 ; 1.283567e+03 ];
omc_error_11 = [ 5.192014e-03 ; 3.617004e-03 ; 7.430776e-03 ];
Tc_error_11  = [ 6.265222e+00 ; 6.665231e+00 ; 5.332468e+00 ];

