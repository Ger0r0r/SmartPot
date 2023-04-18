import telebot;

with open("token", "r") as stream:
    token = str(stream.read()).split()[0]
with open("known_users", "r") as stream:
    known_usernames = stream.read().split()

bot = telebot.TeleBot(token);

def get_help():
    return "Vsem sasatb"

@bot.message_handler(content_types=['text'])
def get_text_messages(message):
    #print(message.from_user.username)

    if (message.from_user.username not in known_usernames):
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
