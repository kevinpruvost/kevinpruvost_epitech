##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile
##

NAME	= my_defender

CC	= gcc

RM	= rm -f

SRCS	= 	main.c 						\
		window_check.c					\
		is_env_display.c				\
\
		src/destroy.c					\
\
		src/main_menu/create_button.c			\
		src/main_menu/event_button.c			\
		src/main_menu/event_button2.c			\
		src/main_menu/animation.c			\
		src/main_menu/funcs.c				\
\
		src/main_menu/structs/menu_s.c			\
		src/main_menu/structs/menu_s2.c			\
\
		src/htp/funcs.c					\
\
		src/htp/structs/htp_s.c				\
		src/htp/structs/button.c			\
\
		src/lvl/funcs.c					\
		src/lvl/end_game.c				\
		src/lvl/txt_info.c				\
		src/lvl/events.c				\
		src/lvl/draw.c					\
		src/lvl/draw2.c					\
		src/lvl/pause.c					\
		src/lvl/pause_resume.c				\
		src/lvl/spawn.c					\
		src/lvl/path_finding.c				\
		src/lvl/mob_damage.c				\
		src/lvl/mob_killed.c				\
		src/lvl/place_tower.c				\
		src/lvl/display_tower_info.c			\
		src/lvl/tower_shooting.c			\
		src/lvl/proj_move.c				\
		src/lvl/proj_damage.c				\
		src/lvl/actualize_mob_stats.c			\
		src/lvl/sell_tower.c				\
		src/lvl/upgrade_tower.c				\
		src/lvl/dot_behaviour.c				\
		src/lvl/slow_behaviour.c			\
		src/lvl/animation_mobs.c			\
		src/lvl/animation_towers.c			\
		src/lvl/position_range.c			\
		src/lvl/events_tower_mouse.c			\
\
		src/lvl/map/map.c				\
		src/lvl/map/change_map.c			\
		src/lvl/map/generate_random_map.c		\
		src/lvl/map/generate_random_map2.c		\
		src/lvl/map/generate_random_map3.c		\
		src/lvl/map/stuck_map.c				\
		src/lvl/map/clear_map.c				\
		src/lvl/map/map_spriting.c			\
\
		src/lvl/score/score.c				\
\
		src/lvl/structs/mob.c 				\
		src/lvl/structs/proj.c 				\
		src/lvl/structs/lvl_s.c 			\
		src/lvl/structs/tower.c 			\
		src/lvl/structs/player.c 			\
		src/lvl/structs/player2.c			\
		src/lvl/structs/lib_types.c			\
		src/lvl/structs/lib_types_textures.c		\
		src/lvl/structs/tower_infos.c 			\
\
		src/map_editor/funcs.c				\
		src/map_editor/check_map_finished.c		\
		src/map_editor/build_map.c			\
		src/map_editor/check_valid_case.c		\
		src/map_editor/playable.c			\
		src/map_editor/remove_case.c			\
		src/map_editor/events.c				\
		src/map_editor/draw.c				\
\
		src/map_editor/structs/map_editor_s.c           \
		src/map_editor/structs/button.c			\
		src/map_editor/structs/desc.c			\
\
		src/settings/funcs.c				\
		src/settings/create_loading_bars.c		\
		src/settings/events.c				\
		src/settings/draw.c				\
\
		src/settings/structs/settings_s.c               \
		src/settings/structs/return_button.c		\
\
		src/common_structs/sound_object.c		\
		src/common_structs/background_object.c		\
		src/common_structs/game_object.c		\
		src/common_structs/text_object.c           	\
		src/common_structs/game_s.c			\
		src/common_structs/main_funcs.c			\
		src/common_structs/change_page.c		\
		src/common_structs/create_grid.c		\
\
		lib/load_file_in_mem.c				\
		lib/my_atoi.c					\
		lib/my_getnbr.c					\
		lib/my_putstr.c					\
		lib/my_revstr.c					\
		lib/my_strlen.c					\
		lib/str_add.c					\
		lib/is_str.c					\
		lib/float_to_s.c				\
		lib/get_next_line.c				\
\
		lib/csfml/basic_functions.c			\
		lib/csfml/collision.c				\
		lib/csfml/is_buttonreleased.c			\
\
		lib/csfml/time/funcs.c				\
		lib/csfml/is_left_click.c			\
		lib/csfml/mod_scale.c				\
		lib/csfml/set_visible.c				\
		lib/csfml/mod_color.c				\
		lib/csfml/center_game_object.c			\
		lib/csfml/is_in_radius.c			\
		lib/csfml/anim_sprite.c				\

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./include/

CFLAGS += -Wall -Wextra -g -l csfml-window -l csfml-graphics -l csfml-system -l csfml-audio

all: $(NAME)

$(NAME):
	 @$(CC) $(SRCS) -o $(NAME) $(CFLAGS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

test: 	re
	@./$(NAME)
