/* coding: utf-8 */
/**
 * Tarte
 *
 * Copyright 2012-2013, PSI
 * Dual licensed under the BSD or GPL Version 3 (or any later) licenses.
 * !! GPL is STRONGLY recommended !!
 * see: http://donut-lang.org/license/
 */

{ /* vector */
	std::vector<TYPE> uvar(10);
	for(std::size_t i = 0;i<10;++i){
		uvar.at(i) = i;
	}
	XValue x (uvar);
	ASSERT_NO_THROW(x.as< std::vector< TYPE > >());
	std::vector<TYPE> var;
	ASSERT_NO_THROW(x.as(var));
	for(std::size_t i = 0;i<10;++i){
		ASSERT_EQ(uvar[i], var[i]);
	}
}
{ /* const vector */
	std::vector<TYPE> uvar(10);
	for(std::size_t i = 0;i<10;++i){
		uvar.at(i) = i;
	}
	XValue const x (uvar);
	ASSERT_NO_THROW(x.as< std::vector< TYPE > >());
	std::vector<TYPE> var;
	ASSERT_NO_THROW(x.as(var));
	for(std::size_t i = 0;i<10;++i){
		ASSERT_EQ(uvar[i], var[i]);
	}
}
{ /* array - dynamic */
	TYPE* uvar = new TYPE[10];
	for(std::size_t i = 0;i<10;++i){
		uvar[i] = i;
	}
	XValue x (uvar, 10);
	ASSERT_NO_THROW(x.as< std::vector< TYPE > >());
	std::vector<TYPE> var;
	ASSERT_NO_THROW(x.as(var));
	for(std::size_t i = 0;i<10;++i){
		ASSERT_EQ(uvar[i], var[i]);
	}
	delete [] uvar;
}
{ /* array - static */
	TYPE uvar[10];
	for(std::size_t i = 0;i<10;++i){
		uvar[i] = i;
	}
	XValue x (uvar, 10);
	ASSERT_NO_THROW(x.as< std::vector< TYPE > >());
	std::vector<TYPE> var;
	ASSERT_NO_THROW(x.as(var));
	for(std::size_t i = 0;i<10;++i){
		ASSERT_EQ(uvar[i], var[i]);
	}
}
