struct Command
{
    char const *text;
    void (*f)();
};

void nothing() {}

void functionA()
{
    Serial.println("This is function A.");
}

void functionB()
{
    Serial.println("This is function B.");
}

Command commands[]{
    {"doA", functionA},
    {"doB", functionB}};

void setup()
{
    Serial.begin(9600);
    Serial.println("Please enter a command.");
}

void loop()
{
    static void (*f)(){nothing};
    f();

    delay(1000); // Only here for demonstration purposes.
    if (not Serial.available())
    {
        return;
    }

    char text[10]{};
    Serial.readBytesUntil('\n', text, sizeof(text));
    for (Command const &command : commands)
    {
        if (not strncmp(command.text, text, 3))
        {
            f = command.f;
        }
    }
}