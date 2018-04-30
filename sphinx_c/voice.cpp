#include "recognition.cpp"

//int main(int argc, char *argv[])
int main()
{
  char const *cfg;

  // Printing all flags of the code.
  int argc=9;
  char *argv[9];
  argv[0] = "./testing_mic";
  argv[1] = "-inmic";
  argv[2] = "yes";
  argv[3] = "-dict";
  argv[4] = "model/cmudict-en-us.dict";
  argv[5] = "-jsgf";
  argv[6] = "grammar/chess_grammar.jsgf";
  argv[7] = "-hmm";
  argv[8] = "model/cmusphinx-en-us-8khz-5.2";

  printf("\n\n\n\n\n\n");
  printf("ARGC:i %d\n", argc);
  for(int i=0;i<argc;++i) {
    printf("ARG %d: %s", i, argv[i]);
    printf("\n");
  }
  printf("\n\n\n\n\n\n");

  config = cmd_ln_parse_r(NULL, cont_args_def, argc, argv, TRUE);

  /* Handle argument file as -argfile. */
  if (config && (cfg = cmd_ln_str_r(config, "-argfile")) != NULL) {
    config = cmd_ln_parse_file_r(config, cont_args_def, cfg, FALSE);
  }

  if (config == NULL || (cmd_ln_str_r(config, "-infile") == NULL && cmd_ln_boolean_r(config, "-inmic") == FALSE)) {
    E_INFO("Specify '-infile <file.wav>' to recognize from file or '-inmic yes' to recognize from microphone.\n");
    cmd_ln_free_r(config);
    return 1;
  }

  ps_default_search_args(config);
  ps = ps_init(config);
  if (ps == NULL) {
    cmd_ln_free_r(config);
    return 1;
  }

  E_INFO("%s COMPILED ON: %s, AT: %s\n\n", argv[0], __DATE__, __TIME__);

  if (cmd_ln_str_r(config, "-infile") != NULL) {
    // nothing
  } else if (cmd_ln_boolean_r(config, "-inmic")) {
    recognize_from_microphone();
  }

  ps_free(ps);
  cmd_ln_free_r(config);

  return 0;
}
