transportincludedir			= ${pkgincludedir}/transport

EXTRA_DIST += lib/transport/CMakeLists.txt

transportinclude_HEADERS = \
	lib/transport/logtransport.h	\
	lib/transport/transport-aux-data.h	\
	lib/transport/transport-tls.h	\
	lib/transport/transport-file.h	\
	lib/transport/transport-pipe.h	\
	lib/transport/transport-socket.h \
	lib/transport/transport-socket-proxy.h \
	lib/transport/transport-socket-proxy-private.h \
	lib/transport/transport-udp-socket.h \
	lib/transport/transport-factory.h \
	lib/transport/multitransport.h \
	lib/transport/transport-factory-tls.h \
	lib/transport/transport-factory-socket.h \
	lib/transport/tls-context.h \
	lib/transport/tls-verifier.h \
	lib/transport/tls-session.h

transport_sources = \
	lib/transport/logtransport.c	\
	lib/transport/transport-aux-data.c	\
	lib/transport/transport-file.c	\
	lib/transport/transport-pipe.c	\
	lib/transport/transport-socket.c \
	lib/transport/transport-socket-proxy.c \
	lib/transport/transport-udp-socket.c \
	lib/transport/multitransport.c \
	lib/transport/transport-factory-tls.c \
	lib/transport/transport-factory-socket.c \
	lib/transport/tls-context.c \
	lib/transport/tls-verifier.c \
	lib/transport/tls-session.c

transport_crypto_sources = \
	lib/transport/transport-tls.c

include lib/transport/tests/Makefile.am
