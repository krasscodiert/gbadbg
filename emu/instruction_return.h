class instruction_return
{
public:
	const bool get_sign();
	const bool get_zero();
	const bool get_carry();
	const bool get_overflow();

	const unsigned int get_value();

	instruction_return(unsigned int value);
	~instruction_return();

private:
	bool sign;
	bool zero;
	bool carry;
	bool overflow;

	unsigned int value;
};