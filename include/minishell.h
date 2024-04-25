/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:48:57 by picatrai          #+#    #+#             */
/*   Updated: 2024/03/23 10:04:05 by picatrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR_ARGC_ENVP 1
# define ERROR_PROMPT 2
# define ERROR_MALLOC 3
# define ERROR_PIPE 4
# define ERROR_FILE 5
# define ERROR 6
# define SUCCESS_SQUARE 7
# define GOOD_INPUT 0
# define WRONG_INPUT 1
# define WD_BUFFER_SIZE 5000
# define OPEN 0
# define CLOSE 1
# define WORD 1
# define SINGLE_QUOTES 2
# define DOUBLE_QUOTES 3
# define START_DOLLAR 0
# define NOT_START_DOLLAR 1
# define NOT_YET 0
# define YES 1
# define ADD 0
# define DONT_ADD 1
# define CHANGE 0
# define KEEP 1

extern int				g_signal;

enum					e_token_type
{
	TEXT = 0,
	PIPE,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
	INFILE_TEXT,
	OUTFILE_TEXT,
	HEREDOC_TEXT,
	APPEND_TEXT,
	AND,
	OR,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	CMD,
	ARGS,
};

enum					e_tree_type
{
	EXEC_LIST = 0,
	OPPERATOR_AND,
	OPPERATOR_OR,
};

typedef struct s_expand
{
	int					act;
	struct s_expand		*prev;
	struct s_expand		*next;
}						t_expand;

typedef struct s_lst_exec
{
	struct s_lst_exec	*prev;
	struct s_lst_exec	*next;
	t_expand			**expand;
	int					len_expand;
	char				**args;
	int					fd_in;
	int					fd_out;
}						t_lst_exec;

typedef struct s_tree
{
	int					type;
	struct s_tree		*parent;
	struct s_tree		*left_child;
	struct s_tree		*right_child;
	t_lst_exec			*lst_exec;
}						t_tree;

typedef struct s_token
{
	char				*str;
	int					quotes;
	int					type;
	t_expand			*expand;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_data_parse
{
	t_token				*token;
	int					double_quote_open;
	int					single_quote_open;
	int					new_word;
	int					index_str;
	int					index;
	char				*str;
	char				*prompt;
	char				*input;
	int					merge;
	int					index_new_str;
	char				*before;
	char				*after;
	int					i;
	int					part;
	char				*heredoc;
	int					fd_in;
	int					fd_out;
	char				**args_tmp;
	int					index_pipes;
	int					**fd_pipes;
	int					nb_pipes;

	int					*array_hd;
	int					index_here_doc;

	int					tmp;
	t_expand			**expand;

	char				condition_1[4];
	char				*res_1[4];
	char				condition_2[5];
	char				*res_2[5];

	char				*opp[9];
	int					type[9];

	char				**env;
	int					exit_status;

	char				*wildcard;
	int					tmp_wildcard;
	int					found;
}						t_data_parse;

typedef struct s_wildcard
{
	struct s_wildcard	*prev;
	struct s_wildcard	*next;
	char				*str;
}						t_wildcard;

typedef struct s_data_expand
{
	char				**env;
	int					status;
	int					add_next;
	int					index;
	char				**res;
	char				*new_str;
}						t_data_expand;

typedef struct s_process_id
{
	int					*tab_pid;
	int					index;
}						t_tab_pid;

enum					e_bool
{
	FALSE = 0,
	TRUE
};

//ft_parse.c
int						ft_parse(t_tree **tree, t_data_parse *data_parse,
							char **env, int *exit_status);

// # ====================================================== #
// |														|
// |				start									|
// |														|
// # ====================================================== #

//ft_get_prompt.c
char					*ft_get_prompt(char **env);
char					*ft_at_user(char *start_prompt, char *end_prompt);
char					*ft_at_home(char *start_prompt, char *end_prompt,
							char *str);
char					*ft_at_else(char *start_prompt, char *end_prompt,
							char *str);

//signaux.c
void					ft_display_new_prompt(int signal);
int						ft_change_sig(void);
int						ft_set_sig(void);
void					print(int signal);

// # ====================================================== #
// |														|
// |				tokenisation							|
// |														|
// # ====================================================== #

//check_wildcard.c
int						ft_strchr_wildcard(char *str, char *find,
							int index_str);
int						ft_check_all(char **split, char *str);
int						ft_check_before(char *to_find, char **split, char *str);
int						ft_check_after(char *to_find, char **split, char *str);

//condition_grammaire_1.c
int						ft_check_parenthesis(t_token *token);
int						ft_check_proximity_opperator_bonus_suite(
							t_token *token);
int						ft_check_proximity_opperator_bonus(t_token *token);
int						is_cmd_between_bonus_opperator(t_token *token);
int						ft_condition_grammaire(t_token *token);

//condition_grammaire_2.c
int						ft_is_quote_close(char *input,
							int double_quote_open,
							int single_quote_open);
int						ft_check_pipes(t_token *token);
int						is_redirection_well_followed(t_token *token);
void					print_no_cmd(char *str);
int						ft_no_cmd(t_token *token);

//ft_add_token.c
void					ft_set_add_token(t_data_parse *data_parse);
int						ft_add_token_end(t_data_parse *data_parse);
int						ft_add_token(t_token **token, t_data_parse *data_parse,
							t_expand *expand);
int						ft_add_and_return(t_data_parse *data_parse,
							t_token **token,
							t_expand *expand);

//ft_make_token.c
int						ft_set_make_token(t_data_parse *data_parse);
int						ft_gestion_quotes_close(t_data_parse *data_parse,
							t_expand *expand,
							t_token **token);
int						ft_gestion_quotes(t_data_parse *data_parse,
							t_expand *expand,
							t_token **token);
int						ft_maybe_empty(t_data_parse *data_parse);
int						ft_make_token(t_data_parse *data_parse,
							t_token **token);

//ft_tokenisation.c
int						ft_tokenisation(t_token **token,
							t_data_parse *data_parse);

//ft_wildcard_1.c
int						condition_maybe_wildcard(char **isol, char ***split,
							t_wildcard *ls, t_data_parse *data_parse);
int						ft_maybe_a_wildcard(t_data_parse *data_parse);
int						ft_set_wildcard(t_data_parse *data_parse);
char					*ft_wildcard(t_data_parse *data_parse);

//ft_wildcard_2.c
char					*ft_isol_word(t_data_parse *data_parse);
int						ft_condition_wildcard_2(int *found, char **wildcard,
							t_wildcard *ls);
int						ft_all_wildcard(t_wildcard *ls, char **wildcard);
int						ft_set_maybe_a_wildcard(char **isol, char ***split,
							t_wildcard *ls, t_data_parse *data_parse);
int						ft_end_maybe_wildcard(int found,
							t_data_parse *data_parse, char *isol, char **split);

//ft_wildcard_3.c
int						set_ls(t_wildcard **ls);
int						ft_set_add_wildcard(char ***split, char *add,
							char ***new);
char					**ft_no_wildcard(char *add, char **base);
int						ft_condition_wildcard(int *found, char **base,
							char ***new, t_wildcard *ls);

//ft_isol_operator.c
char					*ft_isol_operator(t_data_parse *data_parse);
void					ft_set_add_in_opperator(t_data_parse *data_parse);
void					ft_change_status_quotes(t_data_parse *data_parse);
int						ft_add_in_opperator_suite(t_data_parse *data_parse);
int						ft_add_in_opperator(t_data_parse *data_parse);

//set_grammaire.c
void					ft_set_redirection_text(t_token **token);
void					ft_set_cmd_args(t_token **token);
void					ft_set_all_grammaire(t_token **token);

// # ====================================================== #
// |														|
// |					binary_tree							|
// |														|
// # ====================================================== #

//cut_token.c
int						ft_is_there_parenthesis(t_token *token);
t_token					*without_parenthesis(t_token *token);
t_token					*before_token(t_token *token);
t_token					*after_token(t_token *token);

//ft_create_tree_1.c
int						ft_add_node(t_tree **tree, t_token *token,
							t_data_parse *data_parse, t_token *tmp);
int						ft_suite_add_node(t_tree **tree, t_token *token,
							t_token **new, t_data_parse *data_parse);
void					ft_complete_tree_first_step(t_token **token,
							int *parenthesis_open);
int						ft_complete_tree(t_tree **tree, t_token *token,
							t_data_parse *data_parse);

//ft_create_tree_2.c
int						ft_add_tree_null(t_tree **tree, t_tree *new,
							t_token *token, t_data_parse *data_parse);
int						ft_add_tree_no_null(t_tree **tree, t_tree *new,
							t_token *token, t_data_parse *data_parse);
int						ft_add_tree(t_tree **tree, t_tree *new, t_token *token,
							t_data_parse *data_parse);
int						ft_complete_tree_part_2(t_tree **tree, t_token *tmp,
							t_token **new, t_data_parse *data_parse);

//ft_interpret_token_1.c
int						ft_is_token_type_1(t_token *token);
int						ft_is_token_type_2(t_token *token);
int						ft_interpret_token_suite(t_data_parse *data_parse,
							t_lst_exec **lst_exec,
							t_token **token);
int						ft_interpret_token(t_data_parse *data_parse,
							t_lst_exec **lst_exec,
							t_token **token);

//ft_interpret_token_2.c
int						ft_exec_token_type_1(t_data_parse *data_parse,
							t_lst_exec **lst_exec,
							t_token *token);
int						ft_exec_token_type_infile(t_data_parse *data_parse,
							t_token *token);
int						ft_exec_token_type_outfile(t_data_parse *data_parse,
							t_token *token);
int						ft_exec_token_type_2(t_data_parse *data_parse,
							t_token *token);

//here_doc.c
int						ft_exec_token_type_heredoc(t_data_parse *data_parse,
							t_token **token);
int						ft_nb_here_doc(t_token *token);
int						ft_complete_here_doc(t_data_parse *d_p, t_token *token,
							int index, int *exit_status);
int						ft_complete(int fd_in, t_token *token,
							t_data_parse *data_parse, int *exit_status);
char					*ft_here_doc(void);

//make_lst_exec.c
int						ft_nb_lst_exec(t_token *token);
int						ft_one_more_exec(t_data_parse *data_parse,
							t_lst_exec **lst_exec);
int						ft_set_exec(t_data_parse *data_parse,
							t_lst_exec **lst_exec,
							t_token *token);
int						ft_lst_exec(t_token *token, t_lst_exec **lst_exec,
							t_data_parse *data_parse);
int						ft_create_tree(t_tree **tree, t_token *token,
							t_data_parse *data_parse, int *exit_status);

//pipes.c
void					ft_pipes_fail(int **fd_pipes, int index_pipes);
int						ft_nb_pipes(t_token *token);
int						ft_exec_token_type_pipe(t_data_parse *data_parse,
							t_lst_exec **lst_exec);

// # ====================================================== #
// |														|
// |						expand							|
// |														|
// # ====================================================== #

//expand_here_doc_1.c
char					*ft_add_env_expand_hd(char *str, char *new_str, \
		int index, char **env);
char					*ft_cat_env_variable_expand_hd(char *new_str, \
		char *str, int *index, char **env);
char					*ft_expand_here_doc(char *str, char **env, int status);

//expand_here_doc_2.c
int						ft_set_expand_hd(char **new_str, \
		int *index, int *single_quotes, int *double_quotes);
int						ft_is_an_end(char *str, int index);
void					ft_change_quotes(char *str, int *single_quotes, \
		int *double_quotes, int index);
int						rep_status_expand_here_doc(int *index, \
		char **new_str, int status);
int						ft_not_replace_expand_hd(char *str, char **new_str, \
		int index, int single_quotes);

//expand_redirection.c
char					*ft_ambiguous_redirect(char *str, char **split,
							char *new);
char					*transfo_expand(char *str, t_expand *expand,
							t_data_parse *data_parse);
int						ft_set_replace_env_variable(char **new_str, int *index);
char					*ft_replace_env_variable(char *str, t_expand *expand,
							char **env, int status);

//ft_cat_env_variable.c
int						ft_lim_isolate(char *str, int index);
char					*ft_str_isolate(char *str, int index_debut,
							int index_fin);
char					*ft_add_env(char *str, char *new_str, int index,
							char **env);
char					*ft_cat_env_variable(char *new_str, char *str,
							int *index, char **env);

//ft_make_lst_expand.c
int						ft_make_lst_expand(t_expand **expand,
							t_data_parse *data_parse);
int						ft_size_expand(t_expand **expand);
int						ft_complete_expand(t_expand ***expand, t_expand *add,
							int size);
t_expand				**ft_dup_array_expand(t_expand **expand, int size);

//ft_new_args.c
int						is_no_empty(char **arg);
char					**ft_without_empty(char **new_args);
char					**ft_new_args(t_lst_exec *lst_exec, int status,
							char **env);

//ft_replace_env_variable_1.c
int						ft_set_add(char ***res, char **new_str, char **new_args,
							t_data_expand *data_expand);
int						reset_the_buffer(t_data_expand *data_expand,
							char ***res, char **new_str, int len);
char					**end_add(char *new_str, char ***res,
							t_data_expand *data_expand, char *str);
char					**ft_add_and_replace_env_variable(char *str,
							t_expand *expand, t_data_expand *data_expand,
							char **new_args);

//ft_replace_env_variable_2.c
int						ft_not_replace(char *str, char **new_str, int index,
							t_expand **expand);
int						rep_status(int *index, char **new_str, int status,
							t_expand **expand);
char					**ft_add_to_2d_expand(char **base, char *add);
int						ft_add_replace_status(t_data_expand *data_expand,
							char ***res, char **new_str, t_expand **expand);
int						ft_add_classique(t_data_expand *data_expand,
							char ***res, char **new_str, char *str);

//ft_split_add_expand.c
int						ft_set_split_add_expand_part1(char ***split,
							char **new_str, int *add_next, int *add_start);
int						ft_set_split_add_expand_part2(char ***new, char ***res,
							char **split);
int						ft_clear_buffer_in_split_expand(int index, char ***new,
							int add_start, char **split);
int						ft_not_found(char **split, char ***new, int add_start);
int						ft_split_add_expand(char *new_str, char ***res,
							int *add_next);

// # ====================================================== #
// |														|
// |						utils								|
// |														|
// # ====================================================== #

//free_1.c
void					ft_free_token(t_token **token);
void					free_tokenisation_2(t_token **token,
							t_data_parse *data_parse);
void					free_tokenisation_1(char *input, t_token **token);
void					free_2d(char **str);
void					ft_print_error_malloc(void);

//free_2.c
void					free_mini_expand(t_expand *expand);
void					free_tab_tab(char **tab);
void					ft_free_wildcard(t_wildcard **ls);
void					ft_free_pipes(int **fd_pipes, int nb_pipes);
void					close_hd(int *array, int index);

//free_and_close_tree.c
void					free_expand(t_expand **expand, int len);
void					free_close_exec_list(t_lst_exec *exec);
void					free_close_tree(t_tree *tree);
void					free_and_close_tree(t_tree *tree);

//ft_join_utils.c
char					*ft_strjoin_equal_val(char *s1, char *s2);
char					*ft_strjoin_path_without_free(char *s1, char *s2);
char					*ft_strjoin_wihtout_free(char *s1, char *s2);
char					*ft_strjoin_path(char *s1, char *s2);

//ft_utils_1.c
void					ft_putstr_fd(char *s, int fd);
int						ft_strlen(char *str);
int						ft_strncmp(char *s1, char *s2, int n);
int						ft_occ(char *str, char c);
int						ft_strchr(char *str, char *find);

//ft_utils_2.c
int						ft_size_malloc_long_long(long long nb);
char					*ft_itoa_long_long(long long nb);
char					*ft_str_cat_long_long(char *new_str, long long status);
char					**ft_add_2d_to_2d(char **base, char **add);
char					**ft_add_to_2d(char **base, char *add);

//ft_utils_3.c
int						ft_lstsize(t_token *token);
int						ft_isalphanum(int c);
int						ft_strcmp(char *str1, char *str2);
void					print_invalid_token(char *str);
char					*ft_strdup(char *str);

//ft_utils_4.c
void					ft_free_2d_index(char **str, int index);
int						ft_strlen_2d(char **str);
char					**ft_join_2d_args_null(char *str, char **new);
char					**ft_join_2d(char **args_cmd, char *str);
int						is_input_only_whitespace(char *str);

//ft_utils_5.c
int						count_world(char const *s, char sep);
char					*dup_word(char const *s, int start, int end);
char					**ft_split(char *s, char c);
int						ft_len_tab_tab(char **env);

//ft_utils_6.c
char					*ft_get_str(char *str);
int						ft_count_itoa(int n);
char					*ft_itoa(int n);
int						ft_is_ascii(char c);
char					*ft_strjoin_1_malloc(char *str1, char *str2);

//ft_utils_7.c
char					*ft_join_char(char *str, char c);
char					*ft_strjoin(char *str1, char *str2);
char					**ft_strdup_2d(char **str);
char					*ft_strjoin_1_malloc_expand(char *str1, char *str2);
void					ft_end_1(int size, int *exit_status);

//ft_utils_debug.c
void					print_tab_tab(char **tab);

//ft_utils_linked_list.c
void					print_linked_list(t_lst_exec *lst_exec);
int						ft_linked_list_size(t_lst_exec *lst);

//lst_exec.c
t_lst_exec				*ft_new_lst_exec(char **args, int fd_in, int fd_out,
							t_expand **expand);
t_lst_exec				*ft_lst_exec_last(t_lst_exec *lst_exec);
int						ft_lst_exec_add_back(t_lst_exec **lst_exec,
							t_lst_exec *new);

//lst_expand.c
t_expand				*ft_new_expand(int act);
t_expand				*ft_last_expand(t_expand *expand);
int						ft_add_back_expand(t_expand **expand, t_expand *new);

//lst_token.c
t_token					*ft_lstlast(t_token *token);
t_token					*ft_lstnew(char *str, int quotes, int type,
							t_expand *expand);
t_token					*ft_lstnew_no_malloc(char *str, int quotes, int type,
							t_expand *expand);
int						ft_lst_add_back(t_token **token, t_token *new);

//lst_tree.c
int						ft_add_left_child(t_tree **tree, t_tree *new);
int						ft_add_right_child(t_tree **tree, t_tree *new);
t_tree					*ft_tree_new(int type);
t_tree					*ft_first_empty_child(t_tree *tree);

//lst_wildcard.c
t_wildcard				*ft_lst_wildcard_new(char *str);
t_wildcard				*ft_lst_wildcard_last(t_wildcard *ls);
int						ft_lst_wildcard_add_back(t_wildcard **ls,
							t_wildcard *new);

//new_readline.c
int						ft_set_new_readline(char **new, char **read_str,
							int *size);
char					*ft_handle_ctrl_c(char *new, char *read_str);
char					*ft_handle_ctrl_d(char *new, char *read_str, char *lim);
char					*ft_end_2(int size, char *new, char *read_str,
							char *lim);
char					*new_readline(char *lim, int *exit_status);

//print_token_tree.c
void					ft_print_expand(t_expand *expand);
void					ft_printf_2d(char **str, t_expand **expand);
void					ft_print_lst_exec(t_lst_exec *lst_exec);
void					ft_print_tree(t_tree *tree);
void					ft_print_token(t_token **token);

// # ====================================================== #
// |														|
// |					EXPORT								|
// |														|
// # ====================================================== #

void					print_tab_tab(char **tab);
void					clean_env_value(char ***new_env);
void					ft_print_env_ascii_order(char **env);
void					print_tab_tab_ascii_order(char **tab);
void					ft_add_export_value(char **export, char *str);
int						ft_is_ascii(char c);
int						ft_strlen(char *str);
int						ft_find_back_s(char *str);
int						ft_len_tab_tab(char **env);
int						equal_or_nothing(char *str);
int						check_after_equal(char *export);
int						value_start_equal(char *export);
int						ft_check_export_name(char *str);
int						ft_check_empty_export(char *export);
int						ft_strcmp_ascii_order(char *s1, char *s2);
int						ft_is_export_in_env(char **env, char *str);
int						ft_strncmp_exec(char *s1, char *s2, size_t size);
int						ft_find_export_index(char **env, char *str);
int						ft_export_name(char *str, char **export_name);
int						ft_realloc_env(char ***env, int size);
char					*add_null(char *export);
char					*ft_find_export_name(char *str);
char					*export_and_equal(char *export);
char					*export_and_empty(char *export);
char					*add_quote_to_value(char *export);
char					*add_equal_null_char(char *export);
char					*ft_str_dup_env(char *s1, char *s2);
char					*assign_export_empty_value(char *export);
char					*ft_change_shlvl_export(char *shlvl);
char					**dup_env(char **env);
char					**dup_env_ascii_order(char **env);
int						ft_get_path_in_env(char **envp, char ***env, int *i);
void					ft_check_missing_env_2(char **env_val, char ***env,
							int *i);
void					ft_check_missing_env(char ***env, int *i);
char					*ft_get_export_value(char *str);
int						ft_check_if_i_print_env_i(char *str);
void					ft_change_export(char ***env, char *str);
int						ft_do_the_export(char ***env, char *export_str);
int						ft_export(char ***env, char **arg, int free);

// # ====================================================== #
// |														|
// |					UNSET								|
// |														|
// # ====================================================== #

int						ft_unset_is_in_env(char **env, char *unset_str);
int						ft_find_unset_index(char **env, char *unset_str);
int						ft_copy_env_exept_unset(char **env, int unset_index);
int						ft_unset(char ***env, char **cmd);

// # ====================================================== #
// |														|
// |						CD								|
// |														|
// # ====================================================== #
void					ft_change_pwd_old_pwd2(char ***env, char *current_path);
void					ft_change_pwd_old_pwd(char *current_path,
							char *new_path,
							char ***env);
int						is_export_name_in_env(char **env, char *str);
int						ft_cdpath(char **pathtab, char **env);
int						ft_msg_err_chdir(char *str);
void					ft_msg_err_getcwd(void);
int						ft_get_env_value2(char **env_name, char *env, char *str,
							char **env_value);
char					*ft_get_env_value(char **env, char *str);
int						ft_cd_parsing(char **path_tab);
int						ft_cd_home(char ***env);
int						ft_cd_dash(char ***env);
int						ft_cd_cdpath(char **path_tab, char ***env);
int						ft_cd(char **path_tab, char ***env);

// # ====================================================== #
// |														|
// |					ECHO								|
// |														|
// # ====================================================== #

int						ft_check_echo_param_only_one(char *str);
void					ft_check_echo_param(char **tab, int *j, int *param);
int						ft_echo2(char **tab, int i, int param);
int						ft_echo_2_1(char **tab, int *i);
int						ft_echo(char **tab);

// # ====================================================== #
// |														|
// |						PWD								|
// |														|
// # ====================================================== #

char					*ft_get_builtin_err_msg(char *builtin);
int						ft_pustr_builtin_pwd(char *str);
int						ft_pwd(char **tab, char **env);

// # ====================================================== #
// |														|
// |					EXIT								|
// |														|
// # ====================================================== #

enum e_bool				ft_atoi(char *str, long long int *res);
int						ft_check_exit_char(char *str);
void					ft_exit_parsing(char **arg,
							long long int *exit_value, int *exit_flag);
int						ft_exit(char **arg, int *exit_flag);

// # ====================================================== #
// |														|
// |						ENV								|
// |														|
// # ====================================================== #

int						ft_pustr_builtin_env(char *str);
int						ft_env(char **env);

// # ====================================================== #
// |														|
// |						EXEC							|
// |														|
// # ====================================================== #

// char	*ft_get_err_msg(char *cmd, char *msg);
int						ft_is_builtin(char **cmd);
int						check_absolute_path_builtin(char **arg);
int						ft_exec_builtin(char **arg, char ***env, int *exit_flag,
							t_tree *tree);
int						ft_exec_cmd_fork(t_tree *tree, char ***env, int status, \
							t_tab_pid pid);
int						ft_tree_exec(t_tree *tree, char ***env, int *status);
int						ft_find_builtin(char *cmd, char **cmd_tab, char ***env, \
							int *exit_flag);
char					*ft_itoa_shlvl(int nb);
char					**ft_copy_env(char **envp);
char					*ft_change_shlvl(char **envp, char *shlvl);
int						ft_check_shlvl_export(char ***env, char *export_str);
void					ft_replace_last_command(char ***env, char **str);
char					*ft_get_path(void);

// # ====================================================== #
// |														|
// |				CHOOSE AND CHECK CMD					|
// |														|
// # ====================================================== #

char					**ft_get_path_cmd(char **env);
int						ft_check_cmd(char *cmd);
void					free_exit(char **env, char **cmd);
void					free_check_path(char ***env, char ***cmd, \
							char **msg_err, char ***path_split);
void					ft_check_path_execve(char **path, \
							char ***cmd, char ***env);
void					find_cmd_4(char **cmd, char ***env);
void					find_cmd_5(char ***env, char **cmd);
void					ft_check_path_cmd_2(char **path_split, \
							char ***env, char **cmd);
int						ft_check_path_cmd(char ***env, char **cmd);
int						find_cmd_2(char **cmd, int *status, char ***env);
void					find_cmd_3(char ***env, char **cmd);
int						find_cmd(char ***env, char **cmd);

// # ====================================================== #
// |														|
// |						ERROR							|
// |														|
// # ====================================================== #

void					ft_msg_err_getcwd(void);
int						ft_msg_err_chdir(char *str);

#endif
