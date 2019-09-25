#scripts/kconfig/Makefile

# File name: Makefile (GpioTestDriver/UserApp/)
# Code author: Ramana R (github@Rr42)
# Code version: v1.0
# Application: GPIO test driver user application
# Description:
# 	This code ficitilates easy compilation and testing for the GPIO test driver user application.
# License:
#   Copyright (C) 2019  Ramana R (github@Rr42)
#   
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#   
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#   
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.

CC = gcc
IDIR = ./
CFLAGS = -Wall -I$(IDIR)
OBJ = UappGPIO.o
DEPS = UappGPIO.h

UserApp/: UappGPIO.run

UappGPIO.run: $(OBJ)
	gcc -I$(IDIR) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean: 
	rm -rf *.o *.run
