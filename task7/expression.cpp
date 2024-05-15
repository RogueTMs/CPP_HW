// class Expression {
//   public:
//     virtual *Expression diff();
//     virtual *Expression simplyfy() = 0;
//     virtual std::string get_str();

//     virtual ~Expression(){};
// }

// class Binary : public Expression {
//     Expression *left;
//     Expression *right;

//   public:
//     ~Binary() {
//         delete left;
//         delete right;
//     }
// };

// class Unary : public Expression {
//     Expression *exp;

//   public:
//     ~Unary() { delete exp; }
// };

// class Var : public Unary {
//     std::string name;

//   public:
//     Var(const std::string &name_) : name(name_){};
//     std::string get_str() { return name; }
// }

// class Val : public Unary {
//     int value;

//   public:
//     Val(const std::string &val_) : value(val_){};
//     std::string get_str() { return std::to_string(value); }
// }

// class Add : public Binary {

//   public:
//     Add(const Expression &left_, const Expression &right_)
//         : left(first_), right(right_){};
//     std::string get_str() { return left.get_str() + " + " + right.get_str(); }
// }