import telebot;

with open("token", "r") as stream:
    token = str(stream.read()).split()[0]

bot = telebot.TeleBot(token);

def is_known_username(username):
    known_usernames = ['username1', 'username2']

    return username in known_usernames

def get_help():
    return "Vsem sasatb"

@bot.message_handler(content_types=['text'])
def get_text_messages(message):
    if (not is_known_username(message.from_user.username)):
        bot.send_message(message.from_user.id, "sorry is bot not for you");
        return;

    match message.text:
        case "/help":
            bot.send_message(message.from_user.id, get_help());
        case "/sasatb":  
            bot.send_message(message.from_user.id, "sam sosi");
        case _:
            bot.send_message(message.from_user.id, "Я тебя не понимаю. Напиши /help.")

bot.polling(none_stop=True, interval=0)
