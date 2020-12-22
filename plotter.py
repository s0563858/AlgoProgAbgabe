import matplotlib.pyplot as plt; plt.rcdefaults()
import numpy as np
import matplotlib.pyplot as plt

# objects = ('Reduction', 'Shared')
# y_pos = np.arange(len(objects))
# performance = [0.001090,0.004594]

# plt.barh(y_pos, performance, align='center', alpha=0.5)
# plt.yticks(y_pos, objects)
# plt.xlabel('Zeit in Sekunden')
# plt.title('Programming language usage')

# plt.show()



#;;;;;;;;;      THREADS:      ;;;;;;;;;;;;;;
# import random
# import numpy as np
# import matplotlib.pyplot as plt

# from scipy.interpolate import interp1d

# T =np.array( [1,2,4,6,8,10,12,14,16,18,20,24,28,32])
# power =np.array( [ 0.0012596, 0.0007259, 0.0004797, 0.0005886, 0.0005730, 0.0007344, 0.0007880, 0.00077658, 0.00082656, 0.0009307813, 0.000910601 ,0.0010714, 0.0011050,0.0012538 ])
# power1 =np.array( [ 0.0018961, 0.0010882, 0.0006163, 0.0005535, 0.000568208, 0.00072548, 0.00072319, 0.000731563, 0.00079058, 0.000909390, 0.0009003639, 0.00099605, 0.00109001, 0.0012760497 ])
# power2 =np.array( [ 0.0027015254, 0.0016804414, 0.00116811682, 0.001107135, 0.00119366202, 0.00144486438, 0.00134568738, 0.00138843962, 0.0013937186, 0.00151488296, 0.00154706475, 0.00163789782, 0.001789608, 0.0019520376 ])

# from scipy.interpolate import make_interp_spline, BSpline

# xnew = np.linspace(T.min(), T.max(), 300)

# spl = make_interp_spline(T, power, k=3)
# power_smooth = spl(xnew)
# spl = make_interp_spline(T, power1, k=3)
# power_smooth1 = spl(xnew)
# spl = make_interp_spline(T, power2, k=3)
# power_smooth2 = spl(xnew)

# plt.xlabel('Threads-Anzahl')
# plt.ylabel('Zeit in Sekunden')
# plt.plot(xnew, power_smooth, xnew,power_smooth1, xnew,power_smooth2)
# plt.legend(['RGB to Grayscale', 'Brightness',"Histogramm"], loc='best')
# plt.show()
#;;;;;;;;;      THREADS      ;;;;;;;;;;;;;;


#;;;;;;;;;      VERGLEICH:      ;;;;;;;;;;;;;;
import random
import numpy as np
import matplotlib.pyplot as plt

objects = ('Grayscale', 'Helligkeit', 'Histogramm')
y_pos = np.arange(len(objects))
performanceC = [0.0015803, 0.000686330, 0.0007980]
performanceASM = [0.00060810, 0.00060926, 0.00107450]


index = np.arange(5)
bar_width = 0.35

fig, ax = plt.subplots()
summer = ax.bar(y_pos, performanceASM, bar_width,
        label="My Implementation",color="green")

winter = ax.bar(y_pos+bar_width, performanceC,
        bar_width, label="OpenCV")

ax.set_xlabel('Operation')
ax.set_ylabel('Zeit in Sekunden')
ax.set_xticks(y_pos+bar_width/2)
ax.set_xticklabels(["Grayscale", "Helligkeit",'Histogramm'])
ax.legend()

plt.show()
#;;;;;;;;;      VERGLEICH      ;;;;;;;;;;;;;;
