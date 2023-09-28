root:
ifneq ($(shell id -u), 0)
	$(error You must be root)
endif

install: root
	@useradd -Mrs /bin/false trial 2> /dev/null || true
	gcc -o trial trial.c
	install -m4755 -o trial -g trial trial /usr/bin/trial

uninstall: root
	rm /usr/bin/trial

purge: uninstall
	rm /tmp/trial
	userdel trial
