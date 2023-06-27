#include "Game.h"
#include "Player.h"
#include "defines.h"

#include <iostream>
#include <time.h>
#include <conio.h>
#include <vector>


Game* Game::instance = nullptr;

Game* Game::getInstance()
{
	if (instance == nullptr) {
		instance = new Game();
	}
	return instance;
}

Game::Game()
{
	instance = this;
	uiManager = new UIManager();

	currentGameMode = new MoveMode(this);
	nextGameMode = nullptr;
}

Game::~Game()
{
	delete uiManager;
	delete currentGameMode;
}

void Game::run()
{
	srand(time(NULL));

	while (!this->player->getIsExitRequested())
	{
		currentGameMode->handle(this);

		if (nextGameMode != nullptr)
		{
			delete currentGameMode;
			currentGameMode = nextGameMode;
			nextGameMode = nullptr;
		}
	}

	delete currentGameMode;
}

void Game::generateMaps()
{
	this->dialogues =
	{
		// STORY RELEVANT
		{L"King", L"You enter the castle. The inside is just as intricately decorated as the outside, with not one speck of dust on the floor, the corners void of spiderwebs. The king is sitting atop his throne, looking pointedly at you as you take in your surroundings. You have never seen the king in person. All of your childhood, you've only heard stories of his greatness and seen paintings of his likeness. In person, he looks even more intimidating, each detail sharper than a painting could ever capture. As you approach the throne and kneel in front of him, he gets up and approaches you.\n\nKing: Stand up, " + player->getName() + L". You've answered my call, a wise decision indeed. I hope your journey to my castle helped you train for what is to come as the journey that lies before you is even more treacherous than anything you've experienced before. Now, you might wonder why I have called you here, " + player->getName() + L". It has to do with this.\n\nHe shows you an ancient scroll, the fragile parchment yellowed, signifying its old age.\n\nKing: The situation of this realm is dire. Once prosperous and thriving, it now teeters on the edge of ruin. Darkness threatens to engulf us, the fabric of the land is unraveling. This scroll tells of a way to stop the decay. It tells of an ancient artifact hidden somewhere in this very kingdom. I've sent many of my own strongest soldiers to search for it but in vain. I was about to give up any hope of finding it, when I once again picked up and read the scroll. In it, it mentions the child of a great warrior, a legendary " + player->getRoleString() + L" from the same renowned bloodline, who has the ability to find the artifact. That child is you, " + player->getName() + L". I have fought alongside your father, I knew his extraordinary strength, his skill with the blade. I see that same potential in you. Now, are you ready to take on this quest, a treacherous task through the most forsaken places this kingdom has to offer? Your help will bring you a lifetime of glory.\n\nYou nod, signaling that you are ready to take on the quest bestowed upon you.\n\nKing: Very well, I am glad you will be of help to me. Before you set out, let me entrust you with one of my closest allies, one of the best with skills unrivaled both in- and outside of this kingdom. They shall accompany you on this journey and aid you with the battles that await.\n\nKing: Now make haste. Go with my blessing. The destiny of our land rests in your hands."},
		{L"Village_Guard", L"Oh, you want to go to the city? Alright, I will open the gates for you."},
		{L"City_2_Guard", L""},
		{L"City_3_Guard", L""},
		
		// VILLAGE
		{L"Village_S1_H1", L"Inside the townhall there is a gathering...\nCouncil leader: Hey, you! You too are invited to partake in the gathering! Today we're discussing our communities matters."},
		{L"Village_S1_H2", L"Inside is an old man...\nOld man: Back in my day we...\nYou had to listen to a long lecture about the past..."},
		{L"Village_S1_H3", L"Inside is a group of young children playing warriors...\nYoung Girl #1: I hit you, you're dead!\nYoung Boy #1: No you didn't, I had a magical shield!\nYoung Boy #2: That's not fair!\nThey continued fighting about the legitimacy of using a magical shield..."},

		{L"Village_S1_O1", L"A little girl looks up at you...\nGirl: Why are you so old?\nYou're... not old, are you? ...are you?"},
		{L"Village_S1_O2", L"The old woman is carrying a basket...\nOld woman: My... Please take a cookie, dear...\nYou ate a delicious cookie. It fills you with determination."},

		{L"Village_S2_H1", L"Inside is an older woman...\nWoman: Hello dear, could you please take this apple pie to your mother? It's a thank you for helping me out the other day."},
		{L"Village_S2_H2", L"Inside your mother is cooking...\nMother: Hello, are you back already? It's not time for lunch yet, I will call out to you once it is.\n\nNo, I don't need your help right now, thank you for asking. Now go out and make something of your day."},

		{L"Village_S2_O1", L"Your neighbour calls over to you...\nNeighbour: Hey, there! How are the vegetables in your mother's garden looking this season? Mine are looking fine, I might even have too many, in case your family wants to have some of mine!"},
		{L"Village_S2_O2", L"You approach the village's teacher watching over the children playing by the river...\nTeacher: Looking at the children playing makes me miss my childhood. Remember when we played catch and thought of new games to play every day?"},
		{L"Village_S2_O3", L"You approach some of the village's older men are gathered by the river and fishing...\nRandom man: The fish are practically catching themselves today, it's going to be a great catch!"},

		// CITY 1
		{L"City_1_S1_O1", L"You approach one of the guards...\nGuard: You have to thank the king for the peace in this country. His rule created the peace you know today."},
		{L"City_1_S1_O2", L"You approach the captain of the guard...\nGuard Captain: There is no need for heightened security, this city is the safest around."},
		{L"City_1_S1_O3", L"You approach the guard by the entrance to the castle...\nGuard: Stop! Do you have permission to enter? You show him the king's invitation...\nGuard: You may proceed."},
		{L"City_1_S1_O4", L"You approach one of the two guards standing next to each other...\nGuard: The threats in this town are at an all time minimum. There is no easier time to be a guard on duty than now."},
		{L"City_1_S1_O5", L"You approach the other guard...\nGuard: Our daily life is filled with peace and prosperity. There is no need for the cityfolk to resort to violence."},

		{L"City_1_S2_H1", L"Inside is a fishmonger looking to sell his fresh catch...\nFishmonger: Fresh fish! Fresh fish, caught in the bountiful rivers north of town! Buy fish now, it's fresh!"},
		{L"City_1_S2_H2", L"Inside is the town baker...\nBaker: Freshly baked goods! Indulge in some freshly baked goods!"},

		{L"City_1_S2_O1", L"You approach an older woman...\nWoman: Have you heard? There's talks about another grand ball soon! I need to hire a tailor for my dress before they have too much work on their hands!"},
		{L"City_1_S2_O2", L"You approach an elderly man...\nElderly man: Ever since the king has taken over the throne, this town's infrastructure has been a sight to behold, envied by all the neighbouring kingdoms."},
		{L"City_1_S2_O3", L"You approach a wealthy looking girl and her maid...\nGirl: I cannot wait for the next ball! So many possible suitors vying for my attention! I need to be the fairest maiden attending!"},

		{L"City_1_S3_H1", L"Inside the big house is a wealthy man...\nMan: The king's influence and power gave us a life in luxury. His benevolence is recognized even outside this realm."},
		{L"City_1_S3_H2", L"Inside is a tailor working on a beautiful dress...\nTailor: The rumors about a grand ball are great for my business! Now excuse me, I need to finish this dress."},

		{L"City_1_S3_O1", L"You approach a noble lady...\nNoblewoman: This town is a reminder of the king's magnificence! Everywhere you look, there is splendor attributed to the king's will!"},
		{L"City_1_S3_O2", L"You approach a butler standing outside...\nButler: To serve my master is the highest honor, catering to his every need brings me the greatest of joy!"},
		{L"City_1_S3_O3", L"You approach a musician playing a wonderful melody...\nMusician: Let me sway you with my melodies! They are inspired by the splendor of this city and the magnificence of our king!"},

		{L"City_1_S4_H1", L"Inside is a maid...\nMaid: My lady has gone out for a walk, you might even see her. Her unmatched grace is easily recognizable."},
		{L"City_1_S4_H2", L"Inside is a nobleman...\nNobleman: The king's admirable and wise rule are what makes this kingdom flourish. Without him we would be doomed."},
		{L"City_1_S4_H3", L"Inside are a mother and her daughter...\nDaughter: Mother, can we visit the toy store? I would like to look at the newest dolls."},

		{L"City_1_S4_O1", L"You approach the guard by the town entrance...\nGuard: There is no city safer than this one. The king's guards are trained to be the best."},
		{L"City_1_S4_O2", L"You approach a wealthy looking man...\nMan: The king's favor has blessed us with great splendor. This city is a testament to his good will."},

		{L"City_1_S5_H1", L"Inside is the apothecary stocking up the shelves...\nApothecary: Under the king's rule, ailments are rare! He ensures this town's well-being with his wise rule!"},
		{L"City_1_S5_H2", L"Inside is a merchant looking to sell his wares...\nMerchant: Good day, young traveller! Are you looking to buy my wares? They are of the highest quality for the king's prosperity knows no bounds!"},
		{L"City_1_S5_H3", L"Inside is a scholar studying a book...\nScholar: With the king's encouragement, this town's intellectual prowess is unmatched!"},

		{L"City_1_S5_O1", L"You walk up to a man...\nMan: Did you hear? Rumor has it that the king's throne was made entirely of gold and has been adorned with jewels. This was possible due to his admirable rule and victory over barbarian countries!"},
		{L"City_1_S5_O2", L"You hear a food vendor selling his wares...\nVendor: Come, taste the delicacies this city has to offer! Taste the excellence with each bite!"},

		{L"City_1_S6_H1", L"Inside are a woman and two children...\nChild #1: Mother, can my friend and I go outside to play with other children today?"},
		{L"City_1_S6_H2", L"Inside the town's tavern are a few patrons...\nPatron #1: Let us raise our mugs to the life of good fortune the king has granted us! Cheers!\nOther Patrons: Cheers!"},

		{L"City_1_S6_O1", L"You walk up to a middle-aged woman...\nWoman: The king owns many creatures from exotic places. You can see them in the menagerie."},
		{L"City_1_S6_O2", L"You see a street artist painting on a large canvas...\nArtist: With each stroke of my brush I try to capture this city's excellence. Many before me have tried and failed to capture it's magnificence."},
		{L"City_1_S6_O3", L"You approach an elderly man who introduces himself as the city's historian...\nHistorian: The city's past is filled with tales for extraordinary glory and splendor, yet none of it compares to the prosperity it achieved under the king's reign!"},

		// CITY 2
		{L"City_2_S1_H1", L"Inside is an older woman...\nWoman: Some say that power led to the king's corruption. It's hard to know what to believe in anymore these days."},
		{L"City_2_S1_H2", L"Inside is a scholar...\nScholar: I advise you to stay vigilant. Do not blindly accept everything you've been told. Even the noblest of people can have bad intentions."},
		{L"City_2_S1_H3", L"Inside is a man reading a book...\nMan: Some speak of a dark secret the king holds. I certainly do not believe in foolish rumors like these, yet they persist."},

		{L"City_2_S1_O1", L"You approach the guard by the city gates...\nGuard: Who are we to question the king's rule? I will continue to follow the orders I've been given and keep this town's peace."},
		{L"City_2_S1_O2", L"You approach a group of people...\nA woman turns to speak to you...\nWoman: No matter your personal opinion on the king, his actions and decisions shape our everyday life and course of history for this country."},

		{L"City_2_S2_H1", L"Inside is a tired looking shopkeeper...\nShopkeeper: To the outside, the king's image is that of a benevolent man, yet reality is never the way it seems."},
		{L"City_2_S2_H2", L"Inside is a merchant selling his artisan goods...\nMerchant: Despite his flaws, we must recognize and respect the king's authority. He is our leader after all."},

		{L"City_2_S2_O1", L"You approach a woman standing outside...\nWoman: Sometimes actions speak louder than words and someone who is seemingly charming doesn't have the best intentions."},
		{L"City_2_S2_O2", L"You approach a worker...\nWorker: We're the backbone of this country, without us it would fall apart."},
		{L"City_2_S2_O3", L"You approach a woman...\nWoman: The king's rule is a highly complex topic. Some of his actions are admirable whereas others are highly questionable. One cannot base their opinion on his reign off of one of the facets of his decisions."},

		{L"City_2_S3_H1", L"Inside is a family, the father turns towards you...\nFather: Sometimes you hear of other's discontent with the king's rule, but we shouldn't judge hastily. The king has been fair to us all this time."},
		{L"City_2_S3_H2", L"Inside the lavishly decorated room is a man...\nMan: We're highly fortunate to witness a ruler as magnificent and remarkable as our king. His charm has captivated the heart of the public."},
		{L"City_2_S3_H3", L"Inside is a merchant...\nMerchant: There are cracks in the king's outward image revealing his true intent. Would you like to prepare yourself for what lies ahead of us by buying some of my wares?"},
		{L"City_2_S3_H4", L"Inside is a woman cooking a meal...\nWoman: The public's opinion on the king is very much split, some say he is driven by keeping the folk's best interest at heart, while others have started expressing suspicions about possible ulterior motives."},

		{L"City_2_S3_O1", L"You approach a young man...\nMan: There's rumors of a pact the king made to make his rise to power possible..."},

		{L"City_2_S4_H1", L"Inside is an elderly man...\nMan: I was there when the old king died and the current one rose to power. Everyone was optimistic back then, but in the recent years, the folk's trust in the king seems to have started showing cracks."},
		{L"City_2_S4_H2", L"Inside is a mother watching over her children...\nMother: Sometimes it seems as if the king holds the lives of the citizens to no regard."},

		{L"City_2_S4_O1", L"You approach the guard standing by the city's exit...\nGuard: It is my duty to follow the king's orders and stay loyal to him. One must shed themselves of any doubt growing inside...\nHe has a complicated expression..."},
		{L"City_2_S4_O2", L"The city's apothecary is standing outside...\nApothecary: Similar to any ruler in history, the king's rule has had many achievements and setbacks."},
		{L"City_2_S4_O3", L"You approach an elderly woman...\nWoman: I've heard of many discussion about the king's policies over the span of my life but none have lead to so many differing opinions as are now the case."},

		// CITY 3
		{L"City_3_S1_H1", L"Inside is a weary looking woman...\nWoman: The king's rule has failed us and now our city is left with a crumbling infrastructure and struggling citizens. His reign has to come to an end."},
		{L"City_3_S1_H2", L"Inside is a tired looking man...\nMan: We are insignificant in the king's eyes, shunned due to our social position. He is indifferent toward our suffering in favor of keeping the elite satisfied."},
		{L"City_3_S1_H3", L"Inside is a family...\nMother: The king's favoritism trapped our city in a cycle of poverty.\nFather: He has abandoned us, forgotten about us because he doesn't want to deal with the less glamorous facets of his kingdom."},
		{L"City_3_S1_H4", L"Inside is an old man...\nOld Man : I remember the times before the king's neglect has left us in ruins. During the old king's rule we had it all, the next minute the world around us began to fall.I hope one day this chaos and destruction around turns for the better, but I fear I won't be around long enough to witness that..."},

		{L"City_3_S1_O1", L"You approach the guard by the gates...\nGuard: What are you doing in this godforsaken city? There is nothing here for you, you better leave as soon as possible."},

		{L"City_3_S2_H1", L"Inside is a man that looks like he'd just come home from working...\nMan: It's a struggle to provide for my family, no matter how long I work, the king's taxes make it hard to put food on the table."},
		{L"City_3_S2_H2", L"Inside is a frustrated looking woman...\nWoman: The king holds no regard to our struggles. It is clear he does not care for the common folk in favor of the rich."},
		{L"City_3_S2_H3", L"Inside is a weary man...\nMan: The king's court is living a lavish life, filled with luxury. Yet it is built on the backs of the impoverished, who are invisible to them."},
		{L"City_3_S2_H4", L"Inside is a bitter looking woman...\nWoman: The decay around us mirrors the decay of the king's moralities. We're left to suffer while his court lives a life in luxury, blind to his injustices to the common folk."},

		{L"City_3_S2_O1", L"You approach a middle-aged man...\nMan: The king promised us a life in prosperity and fulfillment, yet his words turned out to be nothing but empty lies. He has broken his vows and left us to rot."},

		{L"City_3_S3_H1", L"Inside is an elderly woman...\nWoman: In the grand scheme of things we are insignificant to the king, nothing but pawns in a sick game of chess. Families are left broken at his feet, our lives suspended by a thread."},
		{L"City_3_S3_H2", L"Inside is a woman sitting at a table...\nWoman: Any glimmer of hope for this country is suffocated by the king's reign that looms over our heads like a dark cloud."},
		{L"City_3_S3_H3", L"Inside is a merchant surrounded by his wares...\nMerchant: This city is a testimony to the king's negligence. He promised us greatness but we received nothing but pain."},
		{L"City_3_S3_H4", L"Inside is the town's apothecary...\nApothecary: This city is forgotten and forsaken, we have had to learn to get by with what we have here. Death rates are high due to the king's negligence, his reign has brought nothing but despair upon us."},

		{L"City_3_S3_O1", L"You approach the guard by the exit...\nGuard: There is nothing for you past these gates, so you might as well just turn around and go back. If you decide to leave, don't say I did not warn you."}
	
	};

	this->storyNpcs =
	{
		{L"Village_Guard", this->boundaries.find(L"Village_Gate")},
		{L"King", this->boundaries.find(L"City_1_Gate")},
		{L"City_2_Guard", this->boundaries.find(L"City_2_Gate_1")},
		{L"Messenger", this->boundaries.find(L"City_2_Gate_2")},
	

		/*
			boundaries
				at end of every city
				at start of most cities
		*/
	};

	this->miniMaps =
	{
		{L"City_1", THUMBNAIL_MAP_CITY_1},
		{L"City_2", THUMBNAIL_MAP_CITY_2},
		{L"City_3", THUMBNAIL_MAP_CITY_3},
		{L"Area_1", THUMBNAIL_MAP_AREA_1},
		{L"Area_2", THUMBNAIL_MAP_AREA_2},
		{L"Area_3", THUMBNAIL_MAP_AREA_3},
		{L"Area_4", THUMBNAIL_MAP_AREA_4},

	};

	this->respawn =
	{
		{L"Area_1", L"Village_2"},
		{L"Area_2", L"City_1_2"},
		{L"Area_3", L"City_2_2"},
		{L"Area_4", L"City_3_2"}
	};
}


Player* Game::loadSaveFile(std::vector<std::wstring> lines)
{
	std::vector<std::wstring> names;
	std::vector<int> roles;

	
	do
	{
		size_t pos = lines[0].find(';');
		names.push_back(lines[0].substr(0, pos));
		lines[0] = lines[0].substr(pos + 1);
	} while (lines[0] != L" " && lines[0] != L";");
	
	do
	{
		size_t pos = lines[1].find(';');
		roles.push_back(std::stoi(lines[1].substr(0, pos)));
		lines[1] = lines[1].substr(pos + 1);
	} while (lines[1] != L" " && lines[1] != L";");

	Player* newPlayer = new Player(this->playerTeam, names[0], (RoleClass)roles[0], std::stoi(lines[2]), std::stoi(lines[3]), std::stoi(lines[4]), std::stoi(lines[5]), std::stoi(lines[6]), std::stoi(lines[7]), std::stoi(lines[9]));

	for (int i = 1; i < names.size(); i++)
	{
		Ally* newAlly = new Ally(this->playerTeam, (RoleClass)roles[i], names[i], std::stoi(lines[2]));
		newAlly->setLevel(std::stoi(lines[2]), (RoleClass)roles[i] == Warrior || (RoleClass)roles[i] == Assassin ? true : false);
	}

	this->currentScreenName = lines[8];
	//add loading for playerstats

	for (int lineNr = 10; lineNr < lines.size(); ++lineNr)
	{
		size_t pos = lines[lineNr].find(';');
		this->boundaries.insert(std::pair<std::wstring, bool>(lines[lineNr].substr(0, pos), stoi(lines[lineNr].substr(pos + 1))));
	}

	return newPlayer;
}

Player* Game::createNewGame()
{
	int classSelection = 0;
	bool confirmed = false;
	std::wstring playerName;
	char input = 'w';
	do
	{
		do
		{
			system("CLS");
			std::wcout << "=============~*+-+*~=============\n Pick a class for your hero\n=================================\n" << std::endl;

			if (classSelection == 0) std::wcout << ">";
			std::wcout << "Warrior\n";

			if (classSelection == 1) std::wcout << ">";
			std::wcout << "Healer\n";

			if (classSelection == 2) std::wcout << ">";
			std::wcout << "Magician\n";

			if (classSelection == 3) std::wcout << ">";
			std::wcout << "Assassin\n" << std::endl;

			input = _getch();
		
			switch (input)
			{
				case 'w':
				case 'W':
				case ARROWKEY_UP: if (classSelection != 0)classSelection--;
					break;
				case 's':
				case 'S':
				case ARROWKEY_DOWN: if (classSelection != 3)classSelection++;
					break;
				default:break;
			}
		} while (input != '\r' && input != ' ');
		std::wcout << "=============~*+-+*~=============\n Pick a name for your hero\n=================================\n" << std::endl;
		std::wcout << "Your name: ";
		std::wcin >> playerName;

		std::wcout << L"Are you happy with your choices?(y/n)\n";
		char choice = _getch();
		switch (choice)
		{
			case 'y':
			case 'Y':
			case '\r': confirmed = true;
				break;
			case 'n':
			case 'N':
			case ESCAPEKEY: break;
			default: continue;
		}
	} while (!confirmed);
	this->boundaries =
	{
		{L"Village_Gate",0},
		{L"City_1_Gate", 0},
		{L"City_2_Gate_1", 0},
		{L"City_2_Gate_2", 0},
		{L"City_3_Gate_1", 0},
		{L"City_3_Gate_2", 0},
		

	};
	return new Player(this->playerTeam, playerName, (RoleClass)classSelection, 1, 0, 0, 40, 1, 1, 0);
}

void Game::makeSaveFile()
{
	std::wofstream file(L"./Savefiles/save.txt", std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file ");
	}
	file.trunc;

	for (auto member : this->playerTeam->members)
	{
		file << member->getName() << ";";
	}
	file << " \n";
	for (auto member : this->playerTeam->members)
	{
		file << member->getRole() << ";";
	}
	file << " \n";
	file << this->player->getStats().level << " \n";
	file << this->player->getGold() << " \n";
	file << this->player->getExp() << " \n";
	file << this->player->getNextExpRequirement() << " \n";
	file << this->player->getWeaponLevel() << " \n";
	file << this->player->canProgress() << " \n";
	file << this->currentScreenName << " \n";
	file << this->player->getBossProgression() << " \n";

	for (auto pair : this->boundaries) {
		file << pair.first << ";" << pair.second << " \n";
	}
	file.close();
	this->getUIManager()->showDialog(L"Game successfully saved!", true);
}
