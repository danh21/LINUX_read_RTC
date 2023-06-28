all:
	cc -o readRTC_by_systemCall readRTC_by_systemCall.c
	cc -o readRTC_by_dev-port readRTC_by_dev-port.c

clean:
	rm readRTC_by_systemCall readRTC_by_dev-port
