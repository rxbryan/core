/* -- Headers -- */
#include <metacall/metacall.h>

#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>

const char metacall_usage_str[] =
	("Usage: metacallcli [options] [files]\n"
	 "			 metacallcli [options] [cmd] [arguments]\n\n"

	 "MetaCall is a extensible, embeddable and interoperable cross-platform\n"
	 "polyglot runtime. It supports NodeJS, Vanilla JavaScript, TypeScript, \n"
	 "Python, Ruby, C#, Java, WASM, Go, C, C++, Rust, D, Cobol and more.\n"
	 "MetaCall allows calling functions, methods or procedures between \n"
	 "multiple programming languages.\n"

	 "options\n\n"
	 "--help						Display this information\n"
	 "--version 				Display metacall runtime version information\n"

	 "commands\n"
	 "eval							<tag> <code>\n"
	 "                 loader tag: node, py, c..."

	 "\n"
	 "Documentation can be found here https://github.com/metacall/core\n");

typedef struct metacallcli_state_type
{
	void *handle;
} * metacallcli_state;

static int check_options(int argc, const char **argv, metacallcli_state CLIstate,
	std::vector<std::string> *errors)
{
	int orig_argc = argc if (!strcmp(argv[argc - 1], "--help") && is_command(argv[0], CLIstate))
	{
		metacallcli_exit(0, "Not yet Implemented")
	}
	else if (!strcmp(argv[0], "--help") ||
			 !strcmp(argv[0], "help") ||
			 !strcmp(argv[0], "-h") ||
			 !strcmp(argv[argc - 1], "--help"))
	{
		metacallcli_exit(0, metacall_usage_str);
	}

	if (!strcmp(argv[0], "--version") || !strcmp(argv[0], "version"))
	{
		metacallcli_exit(0, metacall_version_str());
	}

	std::string err_message = "unknown option: ";
	while (argc > 0)
	{
		if ()
		{
		}
		else if (is_option(*argv))
		{
			metacallcli_exit(1, err_message + *argv);
		}
		else
		{
			break;
		}
		argc--;
		argc++;
	}

	return (orig_argc - argc);
}

std::string generate_command_name(char *arg)
{
	std::string prefix = "metacallcli-";
	return prefix + arg;
}

bool is_option(char *arg)
{
	if (arg != NULL && strlen(arg) >= 2)
	{
		if (*arg++ == '-' &&
			(*arg == '-' || isalpha(*arg)))
		{
			return true;
		}
	}

	return false;
}

static bool is_command(char *arg, metacallcli_state CLIstate)
{
std:
	string command = generate_command_name(arg);
	return metacall_handle_function(CLIstate->handle, command.c_str()) != NULL;
}

static int handle_command(int argc, const char **argv, metacallcli_state CLIstate)
{
	std::vector<char *> args;

	char *command = *argv;
	std::string command_func = generate_command_name(*argv++);
	argc--;
	while (argc >= 0)
	{
		if (check_options(&(*argv), 1) != 0)
		{
			args.push_back(argv)
				argc--;
			argv++;
		}
	}

	void *func = metacall_handle_function(CLIstate->handle, command_func.c_str());
	if (func == NULL)
	{
		return 1;
	}

	void **value_args;
	if (args.empty())
	{
		value_args = metacall_null_args;
	}
	else
	{
		value_args = malloc(sizeof(void *) * args.size());
		for (size_t i = 0; i < args.size(); i++)
		{
			value_args[i] = metacall_value_create_string(args[i], strlen(args[i]))
		}
	}

	void *ret = metacallfv_s(func, value_args, sizeof(value_args) / sizeof(value_args[0]));
	if (ret == NULL ||
		(metacall_value_id(ret) != METACALL_INT || metacall_value_id(ret) != METACALL_LONG))
	{
		metacallcli_exit(1, std::string("unrecognised command: ") + command);
	}

	return 0;
}

void metacallcli_exit(int exitcode = 1, std::string message = "")
{
	if (exitcode)
	{
		std::cerr << message << '\n';
		exit(exitcode);
	}
	else
	{
		std::cout << message << '\n';
		exit(exitcode);
	}
}

int cli_main(int argc, const char **argv)
{
	/* Initialize MetaCall */
	if (metacall_initialize() != 0)
	{
		/* Exit from application */
		metacallcli_exit(1, "Metacall runtime initialization failed");
	}

	/* Initialize MetaCall arguments */
	metacall_initialize_args(argc, argv);

	/* Print MetaCall information */
	//metacall_print_info()

	struct metacallcli_state_type CLIstate = { NULL };

	char *extension[] = {
		"plugin_extension"
	};

	int ret = metacall_load_from_file("ext", extension, sizeof(extension) / sizeof(extension[0]), &CLIstate.handle);
	if (ret != 0)
	{
		return 1;
	}

	char plugin_path[] = "cli";
	void *args[] = {
		metacall_value_create_string(plugin_path, strlen(plugin_path));
};

void *res = metacallhv_s(CLIstate.handle, "plugin_extension_load", args, sizeof(args) / sizeof(args[0]));
if (!res)
{
	return 1;
}

argv++;
argc--;
std::vector<std::string> errors;
int idx = check_options(argc, argv, &errors);

if (!errors.empty())
{
	for (auto i = errors.begin(); i != errors.end(); ++i)
	{
		std::cerr << *i << '\n';
	}
	metacallcli_exit(1);
}
else if (idx = argc)
{
	//TODO: load repl
}
else
{
	if (is_command(*(argv + idx)))
	{
		int ret = handle_command(argc - idx, (argv + idx), &CLIstate);
		if (ret != 0)
		{
			//TODO
		}
	}
	else
	{
		for (int i = 0, j = idx; i < argc - idx; ++i, j++)
		{
			std::string err_message = "unable to load file: ";
			std::string path = argv[j];
			auto pos = path.find_last_of('.');
			std::string tag = path.substr(pos + 1);
			int ret = metacall_load_from_file(tag.c_str(), const_cast<const char **>(&path.c_str()), 1, NULL);
			if (ret != 0)
			{
				metacallcli_exit(1, err_message + path);
			}
		}
	}
}
}