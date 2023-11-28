root:
ifneq ($(shell id -u), 0)
	$(error You must be root)
endif

install: root
	@useradd -Mrs /bin/false shield 2> /dev/null || true
	g++ -o shield shield.cpp
	install -m4755 -o shield -g shield shield /usr/bin/shield

uninstall: root
	rm /usr/bin/shield
