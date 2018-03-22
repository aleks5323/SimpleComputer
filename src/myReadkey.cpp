#include "myReadkey.h"

int rk_readkey(enum keys *key)
{
	char buff[16];
	int read_ch;
	read_ch = read(1,buff,15);
	if( read_ch < 0 ) return -1;
	if( strncmp( buff, "l", 1 )        == 0 ) *key = l_key;
	if( strncmp( buff, "s", 1 )        == 0 ) *key = s_key;
	if( strncmp( buff, "r", 1 )        == 0 ) *key = r_key;
	if( strncmp( buff, "t", 1 )        == 0 ) *key = t_key;
	if( strncmp( buff, "i", 1 )        == 0 ) *key = i_key;
	if( strncmp( buff, "\033[15~", 5 ) == 0 ) *key = f5_key;
	if( strncmp( buff, "\033[17~", 5 ) == 0 ) *key = f6_key;
	if( strncmp( buff, "\033[A", 3 )   == 0 ) *key = up_key;
	if( strncmp( buff, "\033[B", 3 )   == 0 ) *key = down_key;
	if( strncmp( buff, "\033[C", 3 )   == 0 ) *key = left_key;
	if( strncmp( buff, "\033[D", 3 )   == 0 ) *key = right_key;
	if( strncmp( buff, "\n", 1 )       == 0 ) *key = enter_key;
        if(strncmp(buff,"^H",1) == 0) *key = ctrlc;
	return 0;
}

int rk_termsave()
{
  struct termios options;
  FILE * config_file;
  config_file = fopen("config.ini","w");
  fwrite( &options, sizeof(options), 1, config_file );
  fclose( config_file );
  return 0;
}

int rk_termrestore()
{
  struct termios options;
  FILE *config_file;

  if ((config_file = fopen("config.ini", "r")) == 0)
    return -1;

  fread(&options, sizeof(options), 1, config_file);

  return 0;
}

int rk_termregime(int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios options;

  if (tcgetattr(1, &options) != 0)
    return -1;
  if (regime == 1)
    options.c_lflag |= ICANON;
  else
  if (regime == 0)
    options.c_lflag &= ~ICANON;
  else
    return -1;
  if (regime == 0) {
    options.c_cc[VTIME] = vtime;
    options.c_cc[VMIN] = vmin;
    if (echo == 1)
      options.c_lflag |= ECHO;
    else
    if (echo == 0)
      options.c_lflag &= ~ECHO;
    else
      return -1;
    if (sigint == 1)
      options.c_lflag |= ISIG;
    else
    if (sigint == 0)
      options.c_lflag &= ~ISIG;
    else
      return -1;
  }
  if (tcsetattr(1, TCSANOW, &options) != 0)
    return -1;

  return 0;
}
