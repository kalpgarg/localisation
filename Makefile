
# Defines the RPI variable which is needed by rc-switch/RCSwitch.h
CXXFLAGS=-DRPI

all: send codesend RFSniffer codesend_RFSniffer combine combine_rev

send: ../rc-switch/RCSwitch.o send.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi
	
codesend: ../rc-switch/RCSwitch.o codesend.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi
	
RFSniffer: ../rc-switch/RCSwitch.o RFSniffer.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

codesend_RFSniffer: ../rc-switch/RCSwitch.o codesend_RFSniffer.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi
	
combine: ../rc-switch/RCSwitch.o combine.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi
	
combine_rev: ../rc-switch/RCSwitch.o combine_rev.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

clean:
	$(RM) ../rc-switch/*.o *.o send codesend servo RFSniffer codesend_RFSniffer combine combine_rev

