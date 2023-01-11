using System.Reflection;

// Select day and part
int day = int.Parse(args[0]);
int part = int.Parse(args[1]);

// Get solution class and function
string type_name = $"Day{day:D2}.Part{part}";
string method_name = "Run";

Type? type = Type.GetType(type_name);
if (type == null) {
    Console.WriteLine($"Error: Unable to find class {type_name}");
    return;
}

MethodInfo? method = type.GetMethod(method_name, BindingFlags.Static | BindingFlags.Public);
if (method == null) {
    Console.WriteLine($"Error: Unable to find function {method_name} in class {type_name}");
    return;
}

// Run solution
Directory.SetCurrentDirectory($"./day{day:D2}"); // Inputs are copied to the build directory
method.Invoke(null, null);
