#define NO_INPUT -1
#define BACKSPACE 263
#define ENTER '\n'

class Input{
    public:
        static void PollInput();
        static bool IsKeyDown();
        static bool IsKeyDown(int key);
        static int GetKey();

    private:
        static int input;
};
