Remote-Operations-Generic-ROS-PDUs$(OBJ): \
    Remote-Operations-Generic-ROS-PDUs.cpp \
    Remote-Operations-Information-Objects.h \
    Remote-Operations-Generic-ROS-PDUs.h \
    $(HFILES)
	$(CCC) $(CFLAGS) -c $(IPATHS) Remote-Operations-Generic-ROS-PDUs.cpp

Remote-Operations-Information-Objects$(OBJ): \
    Remote-Operations-Information-Objects.cpp \
    Remote-Operations-Useful-Definitions.h \
    Remote-Operations-Information-Objects.h \
    Remote-Operations-Generic-ROS-PDUs.h \
    $(HFILES)
	$(CCC) $(CFLAGS) -c $(IPATHS) Remote-Operations-Information-Objects.cpp

Remote-Operations-Useful-Definitions$(OBJ): \
    Remote-Operations-Useful-Definitions.cpp \
    Remote-Operations-Information-Objects.h \
    Remote-Operations-Useful-Definitions.h \
    Remote-Operations-Generic-ROS-PDUs.h \
    $(HFILES)
	$(CCC) $(CFLAGS) -c $(IPATHS) Remote-Operations-Useful-Definitions.cpp

