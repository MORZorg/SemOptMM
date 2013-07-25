/**
 * @file 		SetArguments.cpp
 * @class 		SetArguments
 * @brief 		Class encompassing a set of arguments
 * @author 		Federico Cerutti <federico.cerutti@acm.org>
 * @copyright	GNU Public License v2
 */

#include "SetArguments.h"

/**
 * @brief Simple constructor
 */
SetArguments::SetArguments()
{
	this->arguments = map<string, Argument *>();
	this->key_assoc = map<int, string>();
}

/**
 * @brief	Add an argument to the set
 * @param[in] arg Pointer to an Argument
 */
void SetArguments::add_Argument(Argument *arg)
{
	this->arguments.insert(pair<string, Argument *>(arg->getName(), arg));
	this->key_assoc.insert(pair<int, string>(arg->getNumber(), arg->getName()));
}

/**
 * @brief		Retuns the cardinality of this set
 * @retval int
 */
int SetArguments::cardinality() const
{
	return (int) this->arguments.size();
}

/**
 * @brief		This method returns the pointer to the Argument whose name is given as parameter
 * @param[in] name	 The name of the argument
 * @retval Argument* The pointer to the Argument object, or NULL if not found
 */
Argument *SetArguments::getArgumentByName(string name)
{
	return this->arguments.at(name);
}

/**
 * @brief		This method returns the pointer to the Argument whose identification number is given as parameter
 * @param[in] num	 The name of the argument
 * @retval Argument* The pointer to the Argument object, or NULL if not found
 */
Argument *SetArguments::getArgumentByNumber(int num)
{
	return this->arguments.at(this->key_assoc.at(num));
}

/**
 * @brief	Check wether or not this set is empty
 * @retval bool
 */
bool SetArguments::empty()
{
	return this->arguments.empty();
}

/**
 * @brief 	Begin of the iterator for this set of arguments
 * @retval SetArgumentsIterator An iterator pointing at the first of the elements of this set
 */
SetArgumentsIterator SetArguments::begin() const
{
	return SetArgumentsIterator((this->arguments.begin()));
}

/**
 * @brief 	End of the iterator for this set of arguments
 * @retval SetArgumentsIterator An iterator pointing at the last of the elements of this set
 */
SetArgumentsIterator SetArguments::end() const
{
	return SetArgumentsIterator(this->arguments.end());
}

/**
 * @brief Check whether this set is a subset of `other`
 * @param[in] other	The other set to check
 * @retval bool
 */
bool SetArguments::is_subset_equal(SetArguments *other)
{
	if (this->empty() && other->empty())
		return true;
	if (this->empty() && !other->empty())
		return true;
	if (!this->empty() && other->empty())
		return false;
	if (this->cardinality() > other->cardinality())
		return false;
	for (SetArgumentsIterator it = this->begin(); it != this->end(); it++)
	{
		if (!other->exists((*it)))
			return false;
	}
	return true;
}

/**
 * @brief Check whether this set is a proper subset of `other`
 * @param[in] other	The other set to check
 * @retval bool
 */
bool SetArguments::is_subset(SetArguments *other)
{
	if ((this->cardinality() < other->cardinality()) &&
			this->is_subset_equal(other))
		return true;
	else
		return false;
}

/**
 * @brief Setminus
 * @param[in] other The other term of the subtraction
 * @param[out] res	The result of the subtraction
 * @retval void
 */
void SetArguments::setminus(SetArguments *other, SetArguments *result)
{
	this->clone(result);
	for (SetArgumentsIterator it = other->begin(); it != other->end(); it++)
	{
		if (result->exists((*it)))
			result->remove((*it));
	}
}

/**
 * @brief 	Check whether or not an argument exists in this set
 * @param[in] arg
 * @retval bool
 */
bool SetArguments::exists(Argument * arg)
{
	return (this->arguments.find(arg->getName()) != this->arguments.end());
}

/**
 * @brief 	Remove an argument from this set
 * @param[in] arg
 * @retval void
 */
void SetArguments::remove(Argument * arg)
{
	this->arguments.erase(arg->getName());
}

/**
 * @brief 	Clone this set
 * @param[in] set The set that will be the new clone
 * @retval void
 */
void SetArguments::clone(SetArguments * set)
{
	for (SetArgumentsIterator it = this->begin(); it != this->end(); it++)
	{
		set->add_Argument((*it));
	}
}

/**
 * @brief Intersect this set the `other` set and write the result in `res`
 * @param[in] other The other term of the intersection
 * @param[out] res	The result of the intersection
 * @retval void
 */
void SetArguments::intersect(SetArguments *other, SetArguments *res)
{
	for (SetArgumentsIterator it = this->begin(); it != this->end(); it++)
	{
		for (SetArgumentsIterator inner = other->begin(); inner != other->end();
				inner++)
		{
			if (*(*it) == *(*inner))
			{
				res->add_Argument(*it);
			}
		}
	}
}

/**
 * @brief 		Overloading of the == operator
 * @param[in] 	other   The other term of the comparison
 * @retval bool
 */
bool SetArguments::operator==(const SetArguments &other) const
{
	if (this->cardinality() != other.cardinality())
		return false;
	for(SetArgumentsIterator it = this->begin(), it2 = other.begin(); it != this->end() and it2 != other.begin(); it++, it2++)
	{
		if ((*it) != (*it2))
			return false;
	}
	return true;
}

SetArguments::~SetArguments()
{
	// TODO Auto-generated destructor stub
}

/**
 * @brief Method for printing the SetArguments
 */
ostream& operator<<(ostream& out, const SetArguments& r)
{
	out << "{";

	SetArgumentsIterator it;
	for (it = r.begin(); it != r.end();)
	{
		out << (*it)->getName();
		//out << (*it)->getName() <<"(#"<<(*it)->getNumber()<<")";
		if (++it != r.end())
			out << " ";
	}
	out << "}";
	return out;
}

/**
 * @brief Setunion
 * @param[in] other The other term of the union
 * @param[out] res	The result of the union
 * @retval void
 */
void SetArguments::setunion(SetArguments *other, SetArguments *result)
{
	this->clone(result);
	for (SetArgumentsIterator it = other->begin(); it != other->end(); it++)
	{
		if (!(result->exists((*it))))
			result->add_Argument((*it));
	}
}


/**
 * @brief 		Method for adjust a SetArguments considering the index number of a correct SetArguments
 * @details		Iteration on this SetArguments, look in set_correct, if there is the Argument we put it as arg_correct in this set
				if in the correct set there isn't that argument, we create a new one, using as index one that it isn't already used
 * @param[in]   the SetArguments with the correct Arguments
 * @retval 		A new adjusted SetArguments 
 */
SetArguments * SetArguments::adjust_set(SetArguments * set_correct){
	SetArguments * new_args = new SetArguments();
	int cont=0;
	for(SetArgumentsIterator it = this->begin(); it != this->end(); it++){
		Argument * arg_correct;
		if(set_correct->exists(*it)){
			arg_correct = set_correct->getArgumentByName((*it)->getName());
		}
		else{
			arg_correct = new Argument(**it, (*it)->get_af() ,set_correct->cardinality()+cont);
			cont++;
		}
		new_args->add_Argument(arg_correct);
	}
	return new_args;
}
