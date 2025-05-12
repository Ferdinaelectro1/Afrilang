#pragma once
#include <string>
#include <memory>
#include "lexer.h"

class ASTNode
{
    public: 
      virtual ~ASTNode() = default;
      virtual std::string toCpp() const = 0 ;
};

class NumberNode : public ASTNode
{   
    public:
     std::string toCpp() const override ;
     std::string value;
};

class OperationNode : public ASTNode
{
    public:
      OperationNode(std::unique_ptr<ASTNode> l, std::string op, std::unique_ptr<ASTNode> r);
      std::string toCpp() const override;
      std::string op;
      std::unique_ptr<ASTNode> left;
      std::unique_ptr<ASTNode> right;
};

class VariableNode : public ASTNode
{
    public:
      std::string toCpp() const override;
      std::string name;
};

class PrintNode : public ASTNode
{
    public:
      std::string toCpp() const override;
      std::unique_ptr<ASTNode> chaine;
};

class EqualNode : public ASTNode 
{
    public:
      std::string toCpp() const override;
      std::string op;
      std::unique_ptr<ASTNode> value;
      std::unique_ptr<ASTNode> variable;
};