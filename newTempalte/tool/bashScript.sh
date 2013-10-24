while true; do
	./gen > input
	./sol < input > output.sol
	./bf < input > output.bf

	diff output.sol output.bf
	if [ $? -ne 0 ] ; then break; fi
done
