#ifndef TSP_USA_USA_USA_UTILS_H_
#define TSP_USA_USA_USA_UTILS_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "string/string_utils.h"	/* string_length, stdlib */
#include "file/file_utils.h"		/* file utils */

/* typedefs, struct declarations
 * ────────────────────────────────────────────────────────────────────────── */
struct Location {
	const char *restrict state;
	const char *restrict city;
};


inline void
exit_on_failure(const char *const restrict failure)
{
	file_write_muffle(STDERR_FILENO,
			  failure,
			  string_length(failure));
	exit(EXIT_FAILURE);
}


inline bool
read_file(char *restrict *const restrict buffer_ptr,
	  const char *const restrict path,
	  const char *restrict *const restrict failure)
{
	bool success;
	int file;
	void *restrict buffer;
	struct StatBuffer stat_buffer;

	success = file_open_report(&file,
				   path,
				   O_RDONLY,
				   failure);

	if (LIKELY(success)) {
		success = fstat_report(file,
				       &stat_buffer,
				       failure);

		if (LIKELY(success)) {
			success = malloc_report(&buffer,
						stat_buffer.st_size,
						failure);

			if (LIKELY(success)) {
				success = file_read_report(file,
							   buffer,
							   stat_buffer.st_size,
							   failure);

				if (LIKELY(success)) {
					success = file_close_report(file,
								    failure);

					if (LIKELY(success))
						*buffer_ptr = (char *) buffer;
					else
						free(buffer);

				} else {
					free(buffer);
					file_close_muffle(file);
				}
			} else {
				file_close_muffle(file);
			}
		} else {
			file_close_muffle(file);
		}
	}

	return success;
}


inline bool
write_file(const char *const restrict buffer,
	   const ssize_t size,
	   const char *const restrict path,
	   const char *restrict *const restrict failure)
{
	bool success;
	int file;

	success = file_open_mode_report(&file,
					path,
					O_CREAT | O_TRUNC | O_WRONLY,
					S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH,
					failure);

	if (LIKELY(success)) {
		success = file_write_report(file,
					    buffer,
					    size,
					    failure);

		if (LIKELY(success))
			success = file_close_report(file,
						    failure);
		else
			file_close_muffle(file);
	}

	return success;
}

inline void
get_location(struct Location *const restrict location,
	     char *restrict *const restrict buffer_ptr)
{
	char *restrict buffer;

	buffer = *buffer_ptr;

	location->state = buffer;

	do {
		++buffer;
	} while (*buffer != ',');

	*buffer = '\0';
	++buffer;

	location->city = buffer;

	do {
		++buffer;
	} while (*buffer != ',');

	*buffer = '\0';
	++buffer;

	*buffer_ptr = buffer;
}

inline void
put_location(struct Location *const restrict location,
	     char *restrict *const restrict buffer_ptr)
{
	char *restrict buffer;
	const char *restrict ptr;

	buffer = *buffer_ptr;

	ptr = location->state;

	do {
		*buffer = *ptr;
		++buffer;
		++ptr;
	} while (*ptr != '\0');

	*buffer = ',';
	++buffer;

	ptr = location->city;

	do {
		*buffer = *ptr;
		++buffer;
		++ptr;
	} while (*ptr != '\0');

	*buffer_ptr = buffer;
}



#endif /* ifndef TSP_USA_USA_USA_UTILS_H_ */
