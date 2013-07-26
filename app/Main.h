#ifdef __MAIN_IO_SCHED__

char const * const USAGE_STR = "Usage: ./iosched –s<schedalgo> <inputfile>";



namespace PARAMS
{
  static char schedalgo = 0;
  static char const * inputfile = NULL;
};



void parse_args(int argc, char* argv[])
{
  if (argc < 3)
    throw std::invalid_argument("missing required arguments");

  std::string arg(argv[1]);
  if (arg[0] == '-')
  {
    switch (arg[1])
    {
    case 's':
      if (arg.length() != 3)
        throw std::invalid_argument(
            "invalid value for schedalgo option: " + arg);

      PARAMS::schedalgo = arg[2];
      break;
    default:
      throw std::invalid_argument("unknown option: " + arg);
    }
  }
  else
    throw std::invalid_argument("invalid argument: " + arg);

  PARAMS::inputfile = argv[2];
}

#endif //__MAIN_IO_SCHED__
