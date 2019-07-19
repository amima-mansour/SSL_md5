#include "../inc/ft_ssl.h"
#include "../inc/get_next_line.h"
#include "../libft/libft.h"

static void	print_error(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return;
}

static	char	*file_check(char *str)
{
	int 	fd;
	char	*read;

	if ((fd = open(str, O_RDONLY) == -1))
	{
		ft_putstr("ft_ssl: md5: ");
		ft_putstr(str);
		print_error(": No such file or directory");
		return(NULL);
	}
	if (get_next_line(fd, &read) == 1)
	{
		print_error("Error file");
		read = NULL;
	}
	close(fd);
	return(read);
}

static 	void 	(*cmd_check(char *cmd))(char*, t_flags, char*)
{
	if (ft_strcmp(cmd, "md5") == 0)
		return(&md5);
	if (ft_strcmp(cmd, "sha256") == 0)
		return(&sha256);
	print_error("Not a valid command");
	return(NULL);
}

static 	int flags_check(char **argv, int argc, t_flags *flags)
{
	int i;

	i = 1;
	flags->r = 0;
	flags->p = 0;
	flags->s = 0;
	flags->q = 0;
	while(++i < argc)
	{
		if (ft_strcmp(argv[i],"-r") == 0)
			flags->r = 1;
		else if (ft_strcmp(argv[i],"-p") == 0)
			flags->p = 1;
		else if (ft_strcmp(argv[i],"-s") == 0)
			flags->s = 1;
		else if (ft_strcmp(argv[i],"-q") == 0)
			flags->q = 1;
		else
			break;
	}
	return(i);
}

int		main(int argc, char **argv)
{
	t_flags	flags;
	void	(*cmd)(char*, t_flags, char*);
	int		i;
	char	*msg;

	if (argc < 2) {
		print_error("usage: ft_ssl command [command opts] [command args]");
        return(0);
    }
	if (!(cmd = cmd_check(argv[1])))
		return(0);
	if ((i = flags_check(argv, argc, &flags)) == -1)
		return(0);
	if ((get_next_line(0, &msg) == 1))
	{
		if ((flags.p))
			print_error(msg);
		cmd(msg, flags, NULL);
		free(msg);
	}
	else
	{
		if (i == argc)
		{
			print_error("No File or Sentence to Hash");
			return(-1);
		}
	}
	while (i < argc)
	{
		if ((msg = file_check(argv[i])))
		{
			cmd(msg, flags, argv[i]);
			free(msg);
		}
		i++;
	}
	return(0);
}
