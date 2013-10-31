#include "Motor.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

// return given mumber as a string
string str ( long n ) { ostringstream os; os << n; return os.str(); }
 
// return true iff given character is '0'..'9'
bool isdig ( char c ) { return isdigit(static_cast<unsigned char>(c)) != 0; }
 
 
////////////////////// cell
 
enum cell_type { Symbol, Number, List, Proc, Lambda, Error };
 
struct environment; // forward declaration; cell and environment reference each other
 
// a variant that can hold any kind of lisp value
struct cell {
	typedef cell (*proc_type)(const vector<cell> &);
	typedef vector<cell>::const_iterator iter;
	typedef map<string, cell> map;
	cell_type type; string val; vector<cell> list; proc_type proc; environment * env;
	cell(cell_type type = Symbol) : type(type), env(0) {}
	cell(cell_type type, const string & val) : type(type), val(val), env(0) {}
	cell(proc_type proc) : type(Proc), proc(proc), env(0) {}
};
 
typedef vector<cell> cells;
typedef cells::const_iterator cellit;
 
const cell false_sym(Symbol, "#f");
const cell true_sym(Symbol, "#t"); // anything that isn't false_sym is true
const cell nil(Symbol, "nil");
 
 
////////////////////// environment
 
// a dictionary that (a) associates symbols with cells, and
// (b) can chain to an "outer" dictionary
struct environment {
	environment(environment * outer = 0) : outer_(outer) {}
 
	environment(const cells & parms, const cells & args, environment * outer)
	: outer_(outer)
	{
		cellit a = args.begin();
		for (cellit p = parms.begin(); p != parms.end(); ++p)
			env_[p->val] = *a++;
	}
 
	// map a variable name onto a cell
	typedef map<string, cell> map;
 
	// return a reference to the innermost environment where 'var' appears
	map & find(const string & var)
	{
		if (env_.find(var) != env_.end())
			return env_; // the symbol exists in this environment
		if (outer_)
			return outer_->find(var); // attempt to find the symbol in some "outer" env
		cout << "unbound symbol '" << var << "'\n";
		return env_;
	}
 
	// return a reference to the cell associated with the given symbol 'var'
	cell & operator[] (const string & var)
	{
		return env_[var];
	}
	
private:
	map env_; // inner symbol->cell mapping
	environment * outer_; // next adjacent outer env, or 0 if there are no further environments
};
 
 
////////////////////// built-in primitive procedures
 
cell RenderCube ( const cells & c )
{
	long n(atol(c[0].val.c_str()));
	for (cellit i = c.begin()+1; i != c.end(); ++i) n += atol(i->val.c_str());
	RenderCube ( ( float ) n );
	return cell ( Lambda );
}

cell exit (const cells & c)
{	
	long n(atol(c[0].val.c_str()));
	for (cellit i = c.begin()+1; i != c.end(); ++i) n += atol(i->val.c_str());
	exit(n);
}

cell proc_add(const cells & c)
{
	long n(atol(c[0].val.c_str()));
	for (cellit i = c.begin()+1; i != c.end(); ++i) n += atol(i->val.c_str());
	return cell(Number, str(n));
}
 
cell proc_sub(const cells & c)
{
	long n(atol(c[0].val.c_str()));
	for (cellit i = c.begin()+1; i != c.end(); ++i) n -= atol(i->val.c_str());
	return cell(Number, str(n));
}
 
cell proc_mul(const cells & c)
{
	long n(1);
	for (cellit i = c.begin(); i != c.end(); ++i) n *= atol(i->val.c_str());
	return cell(Number, str(n));
}
 
cell proc_div(const cells & c)
{
	long n(atol(c[0].val.c_str()));
	for (cellit i = c.begin()+1; i != c.end(); ++i) n /= atol(i->val.c_str());
	return cell(Number, str(n));
}
 
cell proc_greater(const cells & c)
{
	long n(atol(c[0].val.c_str()));
	for (cellit i = c.begin()+1; i != c.end(); ++i)
		if (n <= atol(i->val.c_str()))
			return false_sym;
	return true_sym;
}
 
cell proc_less(const cells & c)
{
	long n(atol(c[0].val.c_str()));
	for (cellit i = c.begin()+1; i != c.end(); ++i)
		if (n >= atol(i->val.c_str()))
			return false_sym;
	return true_sym;
}
 
cell proc_less_equal(const cells & c)
{
	long n(atol(c[0].val.c_str()));
	for (cellit i = c.begin()+1; i != c.end(); ++i)
		if (n > atol(i->val.c_str()))
			return false_sym;
	return true_sym;
}
 
cell proc_length(const cells & c)
{
	return cell(Number, str(c[0].list.size())); 
}

cell proc_nullp(const cells & c)
{
	return c[0].list.empty() ? true_sym : false_sym;
}

cell proc_car(const cells & c)
{ 
	return c[0].list[0]; 
}
 
cell proc_cdr(const cells & c)
{
	if (c[0].list.size() < 2)
		return nil;
	cell result(c[0]);
	result.list.erase(result.list.begin());
	return result;
}
 
cell proc_append(const cells & c)
{
	cell result(List);
	result.list = c[0].list;
	for (cellit i = c[1].list.begin(); i != c[1].list.end(); ++i) result.list.push_back(*i);
	return result;
}
 
cell proc_cons(const cells & c)
{
	cell result(List);
	result.list.push_back(c[0]);
	for (cellit i = c[1].list.begin(); i != c[1].list.end(); ++i) result.list.push_back(*i);
	return result;
}
 
cell proc_list(const cells & c)
{
	cell result(List); result.list = c;
	return result;
}
 
// define the bare minimum set of primintives necessary to pass the unit tests
void add_globals(environment & env)
{
	env["nil"] = nil;   env["#f"] = false_sym;  env["#t"] = true_sym;		env["SyntaxError"] = cell(Error);
	env["append"] = cell(&proc_append);   env["car"]  = cell(&proc_car);	env["exit"]		   = cell(&exit);
	env["cdr"]    = cell(&proc_cdr);      env["cons"] = cell(&proc_cons);   env["RenderCube"]  = cell(&RenderCube);
	env["length"] = cell(&proc_length);   env["list"] = cell(&proc_list);
	env["null?"]  = cell(&proc_nullp);    env["+"]    = cell(&proc_add);
	env["-"]      = cell(&proc_sub);      env["*"]    = cell(&proc_mul);
	env["/"]      = cell(&proc_div);      env[">"]    = cell(&proc_greater);
	env["<"]      = cell(&proc_less);     env["<="]   = cell(&proc_less_equal);
}
 
 
////////////////////// eval
 
cell eval(cell x, environment * env)
{
	if (x.type == Symbol)
		return env->find(x.val)[x.val];
	if (x.type == Number)
		return x;
	if (x.list.empty())
		return nil;
	if (x.list[0].type == Symbol) {
		if (x.list[0].val == "quote")       // (quote exp)
			return x.list[1];
		if (x.list[0].val == "if")          // (if test conseq [alt])
			return eval(eval(x.list[1], env).val == "#f" ? (x.list.size() < 4 ? nil : x.list[3]) : x.list[2], env);
		if (x.list[0].val == "set!")        // (set! var exp)
			return env->find(x.list[1].val)[x.list[1].val] = eval(x.list[2], env);
		if (x.list[0].val == "defun")      // (define var exp)
			return (*env)[x.list[1].val] = eval(x.list[2], env);
		if (x.list[0].val == "lambda") {    // (lambda (var*) exp)
			x.type = Lambda;
			// keep a reference to the environment that exists now (when the
			// lambda is being defined) because that's the outer environment
			// we'll need to use when the lambda is executed
			x.env = env;
			return x;
		}
		if (x.list[0].val == "begin") {     // (begin exp*)
			for (size_t i = 1; i < x.list.size() - 1; ++i)
				eval(x.list[i], env);
			return eval(x.list[x.list.size() - 1], env);
		}
	}
											// (proc exp*)
	cell proc(eval(x.list[0], env));
	cells exps;
	for (cell::iter exp = x.list.begin() + 1; exp != x.list.end(); ++exp)
		exps.push_back(eval(*exp, env));
	if (proc.type == Lambda) {
		// Create an environment for the execution of this lambda function
		// where the outer environment is the one that existed* at the time
		// the lambda was defined and the new inner associations are the
		// parameter names with the given arguments.
		// *Although the environmet existed at the time the lambda was defined
		// it wasn't necessarily complete - it may have subsequently had
		// more symbols defined in that environment.
		return eval(/*body*/proc.list[2], new environment(/*parms*/proc.list[1].list, /*args*/exps, proc.env));
	}
	else if (proc.type == Proc)
		return proc.proc(exps);
 
	cout << "not a function\n";
	return cell(Error);
}
 
 
////////////////////// parse, read and user interaction
 
// convert given string to list of tokens
list<string> tokenize(const string & str)
{
	list<string> tokens;
	const char * s = str.c_str();
	while (*s) {
		while (*s == ' ')
			++s;
		if (*s == '(' || *s == ')')
			tokens.push_back(*s++ == '(' ? "(" : ")");
		else {
			const char * t = s;
			while (*t && *t != ' ' && *t != '(' && *t != ')')
				++t;
			tokens.push_back(string(s, t));
			s = t;
		}
	}
	return tokens;
}
 
// numbers become Numbers; every other token is a Symbol
cell atom(const string & token)
{
	if (isdig(token[0]) || (token[0] == '-' && isdig(token[1])))
		return cell(Number, token);
	return cell(Symbol, token);
}
 
// return the Lisp expression in the given tokens
cell read_from(list<string> & tokens)
{
	const string token(tokens.front());
	tokens.pop_front();
	if (token == "(") {
		cell c(List);
		while (tokens.front() != ")")
			c.list.push_back(read_from(tokens));
		tokens.pop_front();
		return c;
	}
	else
		return atom(token);
}
 
// return the Lisp expression represented by the given string
cell read(const string & s)
{
	list<string> tokens(tokenize(s));
	return read_from(tokens);
}
 
// convert given cell to a Lisp-readable string
string to_string(const cell & exp)
{
	if (exp.type == List) {
		string s("(");
		for (cell::iter e = exp.list.begin(); e != exp.list.end(); ++e)
			s += to_string(*e) + ' ';
		if (s[s.size() - 1] == ' ')
			s.erase(s.size() - 1);
		return s + ')';
	}
	else if (exp.type == Lambda)
		return "<Lambda>";
	else if (exp.type == Proc)
		return "<Proc>";
	return exp.val;
}
 
// the default read-eval-print-loop
void repl(const string & prompt, environment * env)
{
	for (;;)
	{
		cout << prompt;
		string line; getline(cin, line);
		cout << to_string(eval(read(line), env)) << '\n';
		repl(prompt, env);
	}
}
 
string get_file_contents(const char *filename)
{
  ifstream in(filename, ios::in | ios::binary);
  if (in)
  {
    string contents;
    in.seekg(0, ios::end);
#pragma warning (disable: 4244)
    contents.resize(in.tellg());
    in.seekg(0, ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
#pragma warning (default: 4244)
}

void replfile(const string & prompt, environment * env, char* file)
{
	Log* log = new Log ( "Motor-Lisp-Log" );
	string fileconts = get_file_contents(file);
	string line = "";
	int lineindex = 0;

	for ( int i = 0; fileconts[i] != '\0'; ++i, lineindex++)
	{
		if ( fileconts[i] != '\n' ){line[lineindex] = fileconts[i];}else {lineindex = 0;}

		log->Writeln ( ( char* ) prompt.c_str ( ) );
		log->Writeln ( ( char* ) to_string(eval(read(line), env)).c_str ( ) );
		replfile ( prompt, env, file );
	}
}
 
void repleval(const string & prompt, environment* env, string code)
{
	for (;;)
	{
		cout << prompt;
		cout << to_string(eval(read(code), env)) << '\n';
	}
}
 
void MotorLispMain ( char* file )
{
	environment global_env;
	add_globals ( global_env);
	replfile ( ">>> ", &global_env, file);
}