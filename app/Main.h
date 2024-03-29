#ifdef __MAIN_IO_SCHED__

char const * const USAGE_STR = "Usage: ./iosched [-v] -s<schedalgo> <inputfile>";



namespace PARAMS
{
  static char schedalgo = 0;
  static char const * inputfile = NULL;
};



void parse_args(int argc, char* argv[])
{
  if (argc < 3)
    throw std::invalid_argument("missing required arguments");

  for (int i = 1; i < argc-1; ++i)
  {

    std::string arg(argv[i]);
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
        case 'v':
          OutFilePrinter::ReportingMode() |= TRACE;
          break;
        default:
          throw std::invalid_argument("unknown option: " + arg);
      }
    }
    else
      throw std::invalid_argument("invalid argument: " + arg);
  }

  PARAMS::inputfile = argv[argc-1];
}

#endif //__MAIN_IO_SCHED__
