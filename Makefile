
BINARY	= diablo

IDIR	= ./header

LIBDIR	= ./lib

SRC	= ./src

SRCS	= $(SRC)/diablo.cpp\
	  $(SRC)/Model.cpp

OBJS	= $(SRCS:.cpp=.o)

HEADERS	= $(IDIR)/*

LIBS	=

CC	= g++

CFLAGS	= -I$(IDIR) -L$(LIBDIR)

%.o: %.cpp $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: 	$(OBJS)
	$(CC) -o $(BINARY) $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(SRC)/*.o

fclean: clean
	rm -f $(BINARY)

re: fclean all

.PHONY:  clean fclean re
