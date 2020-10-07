

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "GpioCtrl.h"


/***************************/

/***************************/

// C_GpioCtrl constructor
C_GpioCtrl::C_GpioCtrl( int gpioNum, dirEnum gpioDir ) 
{
    m_num = gpioNum;
    m_dir = gpioDir;
    exportGpio();
// set direction 
    char s[50];
    snprintf( s, sizeof(s), "/sys/class/gpio/gpio%d/direction", m_num );
    m_fd = open( s, O_WRONLY );
    if( m_fd >= 0 ) {
        if( m_dir == DIR_IN ) { 
            write( m_fd, "in", 2 ); 
            printf( "dir in\n" ); 
        }
        if( m_dir == DIR_OUT ) { 
            write( m_fd, "out", 3 ); 
            printf( "dir out\n" );
            close( m_fd );
        }
    }

// port setup
	snprintf( s, sizeof(s), "/sys/class/gpio/gpio%d/value", m_num );
	m_fd = open(s, (m_dir == DIR_IN) ? O_RDONLY
					: ( m_dir == DIR_OUT ) ? O_WRONLY
					: O_RDWR);
    
}

// C_GpioCtrl destructor
C_GpioCtrl::~C_GpioCtrl() {
	if ( m_fd >= 0 ) close( m_fd );
	unexportGpio();
}

bool C_GpioCtrl::exportGpio()
{
int fd = open( "/sys/class/gpio/export", O_WRONLY );
char s[16];
	if( fd >= 0 ) {
		write( fd, s, snprintf( s, sizeof(s), "%d", m_num ) );
		close( fd );
		return true;
	}
	return false;
}

bool C_GpioCtrl::unexportGpio()
{
int fd = open( "/sys/class/gpio/unexport", O_WRONLY );
char s[16];
	if( fd >= 0 ) {
		write( fd, s, snprintf( s, sizeof(s), "%d", m_num ) );
		close( fd );
		return true;
	}
	return false;
}


bool C_GpioCtrl::setGpio( char value ) {
    if(( m_fd >= 0 ) && ( m_dir != DIR_IN )) {
        write( m_fd, &value, sizeof(value) );
        return true;
    }
    return false;
}

bool C_GpioCtrl::set0() {
    return setGpio('0');
}

bool C_GpioCtrl::set1() {
    return setGpio('1');
}




