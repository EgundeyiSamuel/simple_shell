#include "samd.h"

/**
 * _read_output - reads the output string.
 *
 * @d_eof: return value of read_output function
 * Return: output string
 */
char *_read_output(int *d_eof)
{

	char *output = NULL;
	size_t output_size = 0;

	/* eof to getline */
	*d_eof = read_output(&output, &output_size, stdin);

	/* it should return output or eof */
	return (output);
}

/**
 * set_output - sets the output variable for read_output
 * @output_ptr: Buffer that stores the output string
 * @op_n: Size of output_ptr
 * @result: String that is being assigned to output
 *
 * @ret_n: Size of result
 */
void set_output(char **output_ptr, size_t *op_n, char *result, size_t ret_n)
{

	/* If output_ptr is initially NULL  */
	if (*output_ptr == NULL)
	{
	*op_n = (result_size > MAX_RESULT_SIZE) ? result_size : MAX_RESULT_SIZE;
	/* Assign result to output_ptr */
	*output_ptr = result;
	}

	else if (*op_n < ret_n)
	{

	*op_n = (ret_n > MAX_RESULT_SIZE) ? ret_n : MAX_RESULT_SIZE;

	*output_ptr = result;
	}

	else
	{
	/* Copy the content of result to output_ptr using _copy_str */
	_copy_str(*output_ptr, result);
	/* Free the memory allocated for result */
	free(result);
	}
}

/**
 * read_output - Read output from stream
 * @output_ptr: Buffer that stores the output
 * @op_n: Size of output_ptr
 * @input_stream: Stream to read from
 * Return: The number of bytes read
 */
ssize_t read_output(char **output_ptr, size_t *op_n, FILE *input_stream)
{
	static ssize_t read_bytes;
	ssize_t ret_n;

	read_bytes = 0;
	ret_n = read_or_eof(output_ptr, op_n, input_stream);

	return (ret_n);
}

/**
 * read_or_eof - Read characters until newline or end-of-file
 * @output_ptr: Buffer that stores the output
 * @op_n: Size of output_ptr
 * @input_stream: Stream to read from
 * Return: The number of bytes read
 */
ssize_t read_or_eof(char **output_ptr, size_t *op_n, FILE *input_stream)
{
	int i;
	ssize_t ret_n;
	char *result;

	result = malloc(sizeof(char) * MAX_RESULT_SIZE);
	if (result == NULL)
	return (-1);

	while ((i = fgetc(input_stream)) != '\n' && i != EOF)
	{
	if (read_bytes >= MAX_RESULT_SIZE)
	result = _resize(result, read_bytes, read_bytes + 1);

	result[read_bytes++] = (char)i;
	}

	result[read_bytes] = '\0';
	set_output(output_ptr, op_n, result, read_bytes);

	return (read_bytes);
}
