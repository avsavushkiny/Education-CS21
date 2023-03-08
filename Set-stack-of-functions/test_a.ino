struct Command
{
    char const *text;
    void (*f)();
    bool active;
};

void functionA()
{
    Serial.println("This is function A.");
}

void functionB()
{
    Serial.println("This is function B.");
}

Command commands[]{
    {"doA", functionA, false},
    {"doB", functionB, false}};

void setup()
{
    Serial.begin(9600);
    Serial.println("Please enter a command.");
}

void loop()
{
    delay(1000); // Only here for demonstration purposes.

    for (Command const &command : commands)
    {
        if (command.active)
        {
            command.f();
        }
    }

    if (not Serial.available())
    {
        return;
    }

    char text[10]{};
    Serial.readBytesUntil('\n', text, sizeof(text));
    for (Command &command : commands)
    {
        if (not strncmp(command.text, text, 3))
        {
            command.active = true;
        }
    }
}