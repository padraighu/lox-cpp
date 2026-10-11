import shutil
import subprocess

# some parts are borrowed from //https://github.com/the-lambda-way/CppLox/blob/master/chapter5

def define_type(base_name: str, class_name: str, field_list: list):
    content = ""
    fields = field_list.split(", ")

    content += f"{class_name}::{class_name}({field_list})"
    initialize_fields = []
    for field in fields:
        field_type = field.split(" ")[0]
        name = field.split(" ")[1]
        if field_type in ("LiteralValue", "Token"):
            initialize_fields.append(name)
    if initialize_fields:
        content += " : " + ",".join([f"{name}(std::move({name}))" for name in initialize_fields])
    content += " {\n"
    for field in fields:
        name = field.split(" ")[1]
        if name not in initialize_fields:
            content += f"    this->{name} = std::move({name});\n"
    content += "}\n"

    # visitor
    content += f"std::any {class_name}::accept(Visitor& visitor)\n"
    content += "{\n"
    content += f"    return visitor.visit{class_name}{base_name}(*this);\n"
    content += "}\n\n"

    return content


def define_ast(output_dir: str, base_name: str, types: list):
    path  = f"{output_dir}/{base_name}.cpp".lower()
    content = ""
    content += "#include <memory>\n"
    content += "#include <any>\n"
    content += "#include <utility>\n"
    content += f"#include \"{base_name.lower()}.hpp\"\n\n"

    for type in types:
        class_name = type.split(":")[0].strip()
        fields = type.split(":")[1].strip()
        fields = fields.replace("Expr", "std::shared_ptr<Expr>")
        content += define_type(base_name, class_name, fields)
        content += "\n"

    with open(path, "w") as f:
        f.write(content)

def define_type_header(base_name: str, class_name: str, field_list: list):
    content = ""
    content += f"class {class_name} : public {base_name}\n"
    content += "{\n"
    content += "public:\n"
    # constructor
    content += f"    {class_name}({field_list});\n"
    fields = field_list.split(", ")
    # fields
    for field in fields:
        content += f"    {field};\n"

    content += "    std::any accept(Visitor& visitor);\n"

    content += "};\n"
    return content


def define_ast_header(output_dir: str, base_name: str, types: list):
    path  = f"{output_dir}/{base_name}.hpp".lower()
    content = ""
    content += "#pragma once\n"
    content += "#include <any>\n"
    content += "#include <memory>\n"
    content += "#include \"token.hpp\"\n\n"

    # forward declaration
    content += "class Visitor;\n\n"

    content += f"class {base_name}\n"
    content += "{\n"
    content += "public:\n"
    content += "    virtual std::any accept(Visitor& visitor) = 0;\n"
    content += f"    virtual ~{base_name}() = default;\n"
    content += "};\n\n"

    for type in types:
        class_name = type.split(":")[0].strip()
        fields = type.split(":")[1].strip()
        fields = fields.replace("Expr", "std::shared_ptr<Expr>")
        content += define_type_header(base_name, class_name, fields)
        content += "\n"

    content += define_visitor(base_name, types)

    with open(path, "w") as f:
        f.write(content)


def define_visitor(base_name: str, types: list):
    content = ""
    content += "class Visitor {\n"
    content += "public:\n"
    for type in types:
        type_name = type.split(":")[0].strip()
        content += f"    virtual std::any visit{type_name}{base_name}({type_name} {base_name.lower()}) = 0;\n"
    content += "};\n\n"

    return content


if __name__ == "__main__":
    types = [
        "Binary   : Expr left, Token op, Expr right",
        "Grouping : Expr expression",
        "Literal  : LiteralValue val",
        "Unary    : Token op, Expr right",
    ]
    define_ast_header("src", "Expr", types)
    define_ast("src", "Expr", types)
    if shutil.which("clang-format"):
        subprocess.run(["clang-format", "-i", "src/expr.hpp", "src/expr.cpp"], check=True)
