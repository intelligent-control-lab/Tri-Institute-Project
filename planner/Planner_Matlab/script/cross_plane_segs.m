
clc
clear

planes = [-0.13677271909286323, -0.001307522919873557, -1, 0.35681409561655236;
          -0.09944386985869111, 0.9507137174883696, -1, 0.4148449626591891;
          -0.0028754998304916695, -1, -0.00048562669056519125, -0.1531872239587;
          -0.028656068479931213, -0.9169732738103323, -1, -0.02635994915558708;
          -0.04227291092492677, -0.0017900871745648592, -1, 0.04253270252138967;
          -0.027539864123062554, 0.9174694697754313, -1, -0.02670323898692613;
          0.003517293221011959, -1, -0.0026534115250074763, 0.1535545078421211;
          -0.09670160529976317, -0.9547657737231579, -1, 0.4150487079383617];
      

consider_line = 0;
LineSegs = planes_cross_property(planes,consider_line);


origin_axis3 = [0;0;0];
for i = 1:size(LineSegs,2)
    LineSegs{i}.p = LineSegs{i}.p - origin_axis3;
end

save('data/cross_segs_wpframe.mat','LineSegs')