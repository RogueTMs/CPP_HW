#include <iostream>
#include <memory>
#include <string>

class Expression {
  public:
    Expression() {}

    virtual Expression *diff(std::string var) = 0;
    // virtual Expression* simplyfy() = 0;
    virtual std::string get_str() = 0;
    virtual Expression *get_copy() = 0;

    virtual ~Expression() {}
};

class Val : public Expression {
    int value;

  public:
    Val(int value) : value(value) {}
    Val(const Val &other) : value(other.value) {}

    Expression *diff(std::string var) override { return new Val(0); };

    Expression *get_copy() override { return new Val(*this); }

    std::string get_str() override { return std::to_string(value); }
};

class Var : public Expression {
    std::string name;

  public:
    Var(const std::string &name) : name(name){};

    Var(const Var &other) : name(other.name) {}

    Expression *diff(std::string var) override {
        if (var == name)
            return new Val(1);
        else
            return new Val(0);
    };

    Expression *get_copy() override { return new Var(*this); }

    std::string get_str() override { return name; }
};

class Binary : public Expression {
  protected:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
    char operation;

  public:
    Binary(Expression *left, Expression *right, char operation)
        : left(left), right(right), operation(operation) {}

    // ~Binary() {
    //     std::cout << "BINARY destructor called!" << std::endl;
    //     left.reset();
    //     right.reset();
    // }

    std::string get_str() override {
        // return std::format("{}", " {} ", "{}", left->get_str(), operation,
        // right->get_str());
        return left->get_str() + operation + right->get_str();
    }
};

class Unary : public Expression {
  protected:
    std::shared_ptr<Expression> exp;
    const std::string symb;

  public:
    Unary(std::string symb, Expression *exp) : symb(symb), exp(exp) {}

    // ~Unary() { exp.reset(); }

    std::string get_str() override { return symb + exp->get_str(); }
};

class Add : public Binary {

  public:
    Add(Expression *left, Expression *right) : Binary(left, right, '+'){};

    Expression *get_copy() override { return new Add(*this); }

    Add(const Add &other)
        : Binary(other.left->get_copy(), other.right->get_copy(), '+') {}

    Expression *diff(std::string var) override {
        return new Add(left->diff(var), right->diff(var));
    };
};

class Sub : public Binary {

  public:
    Sub(Expression *left, Expression *right) : Binary(left, right, '-'){};

    Expression *get_copy() override { return new Sub(*this); }

    Sub(const Sub &other)
        : Binary(other.left->get_copy(), other.right->get_copy(), '-') {}

    Expression *diff(std::string var) override {
        return new Sub(left->diff(var), right->diff(var));
    };
};

class Mult : public Binary {

  public:
    Mult(Expression *left, Expression *right) : Binary(left, right, '*'){};

    Expression *get_copy() override { return new Mult(*this); }

    Mult(const Mult &other)
        : Binary(other.left->get_copy(), other.right->get_copy(), '*') {}

    Expression *diff(std::string var) override {
        return new Add(new Mult(left->diff(var), right->get_copy()),
                       new Mult(left->get_copy(), right->diff(var)));
    };

    std::string get_str() override {
        return "(" + left->get_str() + ")" + "*" + "(" + right->get_str() + ")";
    }
};

class Div : public Binary {

  public:
    Div(Expression *left, Expression *right) : Binary(left, right, '/'){};

    Expression *get_copy() override { return new Div(*this); }

    Div(const Div &other)
        : Binary(other.left->get_copy(), other.right->get_copy(), '/') {}

    Expression *diff(std::string var) override{
        return new Div(new Sub(new Mult(left->diff(var), right->get_copy()),
                      new Mult(left->get_copy(), right->diff(var))),
                      new Mult(right->get_copy(), right->get_copy()));};

    std::string get_str() override {
        return "(" + left->get_str() + ")" + "/" + "(" + right->get_str() + ")";
    }
};

class Exponent : public Unary {

  public:
    Exponent(Expression *exp) : Unary("e^", exp){};

    Expression *get_copy() override { return new Exponent(*this); }

    Exponent(const Exponent &other) : Unary("e^", other.exp->get_copy()) {}

    Expression *diff(std::string var) override {
        return new Mult(exp->diff(var), this->get_copy());
    };
};
