Remote-Operations-Generic-ROS-PDUs$(OBJ): \
    Remote-Operations-Generic-ROS-PDUs.c \
    Remote-Operations-Information-Objects.h \
    Remote-Operations-Generic-ROS-PDUs.h \
    $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) Remote-Operations-Generic-ROS-PDUs.c

Remote-Operations-Information-Objects$(OBJ): \
    Remote-Operations-Information-Objects.c \
    Remote-Operations-Useful-Definitions.h \
    Remote-Operations-Information-Objects.h \
    Remote-Operations-Generic-ROS-PDUs.h \
    $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) Remote-Operations-Information-Objects.c

Remote-Operations-Useful-Definitions$(OBJ): \
    Remote-Operations-Useful-Definitions.c \
    Remote-Operations-Information-Objects.h \
    Remote-Operations-Useful-Definitions.h \
    Remote-Operations-Generic-ROS-PDUs.h \
    $(HFILES)
	$(CC) $(CFLAGS) -c $(IPATHS) Remote-Operations-Useful-Definitions.c

