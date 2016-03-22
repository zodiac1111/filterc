/**
 * @file def.h
 *
 */
#ifndef DEF_H_
#define DEF_H_



#define MAX_FILE_PATH_LEN 1024
#define TAG_SUFFIX ".preprocess_tags"

#define TAG_DIR_PREFIX "tags"


#  define CL_RED "\033[31m"
#  define GREEN "\033[32m"
#  define YELLOW "\033[33m"
#  define BLUE "\033[34m"
#  define PURPLE "\033[35m"
#  define CL_ATTR_REV "\033[7m"
#  define CL_ATTR_UNDERLINE "\033[4m"
#  define _COLOR "\033[0m"

#define ATCOMMAND_DEBUG 0
#  define CLOG_INFO(fmt, ...) \
		printf("I"GREEN"(%s:%s)[%d]:"_COLOR fmt "\r\n"\
		,__FILE__,__FUNCTION__,__LINE__ , ##__VA_ARGS__)
#  define CLOG_WARN(fmt, ...) \
		printf("I"YELLOW"(%s:%s)[%d]:"_COLOR fmt "\r\n"\
		,__FILE__,__FUNCTION__,__LINE__ , ##__VA_ARGS__)
#  define CLOG_ERR(fmt, ...) \
		printf("E"CL_RED"(%s:%s)[%d]:"_COLOR fmt "\r\n"\
		,__FILE__,__FUNCTION__,__LINE__ , ##__VA_ARGS__);\
		perror("")
#endif /* DEF_H_ */
