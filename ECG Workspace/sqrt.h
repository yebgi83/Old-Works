#ifndef SQRT_H

#define SQRT_H
double SQRT_Table[255] = {
1.000000000000000,
1.414213562373095,
1.732050807568877,
2.000000000000000,
2.236067977499790,
2.449489742783178,
2.645751311064591,
2.828427124746190,
3.000000000000000,
3.162277660168380,
3.316624790355400,
3.464101615137754,
3.605551275463989,
3.741657386773941,
3.872983346207417,
4.000000000000000,
4.123105625617661,
4.242640687119285,
4.358898943540674,
4.472135954999580,
4.582575694955840,
4.690415759823430,
4.795831523312719,
4.898979485566356,
5.000000000000000,
5.099019513592785,
5.196152422706632,
5.291502622129181,
5.385164807134504,
5.477225575051661,
5.567764362830022,
5.656854249492381,
5.744562646538029,
5.830951894845301,
5.916079783099616,
6.000000000000000,
6.082762530298219,
6.164414002968976,
6.244997998398398,
6.324555320336759,
6.403124237432849,
6.480740698407860,
6.557438524302000,
6.633249580710800,
6.708203932499369,
6.782329983125268,
6.855654600401044,
6.928203230275509,
7.000000000000000,
7.071067811865476,
7.141428428542850,
7.211102550927978,
7.280109889280518,
7.348469228349535,
7.416198487095663,
7.483314773547883,
7.549834435270750,
7.615773105863909,
7.681145747868608,
7.745966692414834,
7.810249675906654,
7.874007874011811,
7.937253933193772,
8.000000000000000,
8.062257748298549,
8.124038404635961,
8.185352771872450,
8.246211251235321,
8.306623862918075,
8.366600265340756,
8.426149773176359,
8.485281374238570,
8.544003745317530,
8.602325267042627,
8.660254037844387,
8.717797887081348,
8.774964387392123,
8.831760866327848,
8.888194417315589,
8.944271909999159,
9.000000000000000,
9.055385138137417,
9.110433579144299,
9.165151389911680,
9.219544457292887,
9.273618495495704,
9.327379053088816,
9.380831519646860,
9.433981132056603,
9.486832980505138,
9.539392014169456,
9.591663046625438,
9.643650760992955,
9.695359714832659,
9.746794344808963,
9.797958971132712,
9.848857801796104,
9.899494936611665,
9.949874371066199,
10.000000000000000,
10.049875621120890,
10.099504938362077,
10.148891565092219,
10.198039027185569,
10.246950765959598,
10.295630140987001,
10.344080432788601,
10.392304845413264,
10.440306508910551,
10.488088481701515,
10.535653752852738,
10.583005244258363,
10.630145812734650,
10.677078252031311,
10.723805294763608,
10.770329614269007,
10.816653826391969,
10.862780491200215,
10.908712114635714,
10.954451150103322,
11.000000000000000,
11.045361017187261,
11.090536506409418,
11.135528725660043,
11.180339887498949,
11.224972160321824,
11.269427669584644,
11.313708498984761,
11.357816691600547,
11.401754250991379,
11.445523142259598,
11.489125293076057,
11.532562594670797,
11.575836902790225,
11.618950038622250,
11.661903789690601,
11.704699910719626,
11.747340124470730,
11.789826122551595,
11.832159566199232,
11.874342087037917,
11.916375287812984,
11.958260743101398,
12.000000000000000,
12.041594578792296,
12.083045973594572,
12.124355652982141,
12.165525060596439,
12.206555615733702,
12.247448713915890,
12.288205727444508,
12.328828005937952,
12.369316876852981,
12.409673645990857,
12.449899597988733,
12.489995996796797,
12.529964086141668,
12.569805089976535,
12.609520212918492,
12.649110640673518,
12.688577540449520,
12.727922061357855,
12.767145334803704,
12.806248474865697,
12.845232578665129,
12.884098726725126,
12.922847983320086,
12.961481396815721,
13.000000000000000,
13.038404810405298,
13.076696830622021,
13.114877048604001,
13.152946437965905,
13.190905958272920,
13.228756555322953,
13.266499161421599,
13.304134695650070,
13.341664064126334,
13.379088160259652,
13.416407864998739,
13.453624047073710,
13.490737563232042,
13.527749258468683,
13.564659966250536,
13.601470508735444,
13.638181696985855,
13.674794331177344,
13.711309200802088,
13.747727084867520,
13.784048752090222,
13.820274961085254,
13.856406460551018,
13.892443989449804,
13.928388277184119,
13.964240043768941,
14.000000000000000,
14.035668847618199,
14.071247279470288,
14.106735979665885,
14.142135623730951,
14.177446878757825,
14.212670403551895,
14.247806848775006,
14.282856857085701,
14.317821063276353,
14.352700094407323,
14.387494569938159,
14.422205101855956,
14.456832294800961,
14.491376746189438,
14.525839046333950,
14.560219778561036,
14.594519519326424,
14.628738838327793,
14.662878298615180,
14.696938456699069,
14.730919862656235,
14.764823060233400,
14.798648586948742,
14.832396974191326,
14.866068747318506,
14.899664425751340,
14.933184523068078,
14.966629547095765,
15.000000000000000,
15.033296378372908,
15.066519173319364,
15.099668870541500,
15.132745950421556,
15.165750888103101,
15.198684153570664,
15.231546211727817,
15.264337522473747,
15.297058540778355,
15.329709716755891,
15.362291495737216,
15.394804318340652,
15.427248620541512,
15.459624833740307,
15.491933384829668,
15.524174696260024,
15.556349186104045,
15.588457268119896,
15.620499351813308,
15.652475842498529,
15.684387141358123,
15.716233645501712,
15.748015748023622,
15.779733838059499,
15.811388300841896,
15.842979517754859,
15.874507866387544,
15.905973720586866,
15.937377450509228,
15.968719422671311
};       

#endif
