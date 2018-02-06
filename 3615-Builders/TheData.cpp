#include "TheData.hpp"

time_t dateTime;

void formatDateTime(uint16_t* date, uint16_t* time) {
	uint16_t y;
	uint8_t m, d, h, min, s;

	// User gets date and time from GPS or real-time clock here
	y = year(dateTime);
	m = month(dateTime);
	d = day(dateTime);
	h = hour(dateTime);
	min = minute(dateTime);
	s = second(dateTime);

	// return date using FAT_DATE macro to format fields
	*date = FAT_DATE(y, m, d);

	// return time using FAT_TIME macro to format fields
	*time = FAT_TIME(h, min, s);
}
   
void TheData::printDirectory(File dir, int numTabs)
{
	while (true)
	{

		File entry = dir.openNextFile();
		if (!entry)
		{
			// no more files
			break;
		}
		for (uint8_t i = 0; i < numTabs; i++)
		{
			Serial.print('\t');
		}
		Serial.print(entry.name());
		if (entry.isDirectory())
		{
			Serial.println("/");
			printDirectory(entry, numTabs + 1);
		}
		else
		{
			// files have sizes, directories do not
			Serial.print("\t\t");
			Serial.println(entry.size(), DEC);
		}
		entry.close();
	}
}

String TheData::convertFrom(uint8_t value)
{
	char c = convertValue[value];
	return String(c);
}

void TheData::setup()
{
	uint8_t v = 65;
	for (uint8_t i = 0; i <= 25; i++)
		convertValue[i] = v++;
	v = 97;
	for (uint8_t i = 26; i <= 51; i++)
		convertValue[i] = v++;
	v = 48;
	for (uint8_t i = 52; i <= 61; i++)
		convertValue[i] = v++;
	dateTime = now();
	SdFile::dateTimeCallback(formatDateTime);
	Sd2Card card;
	if(!card.init(SPI_HALF_SPEED, BUILTIN_SDCARD))
	{
		isStatusOk = false;
		Serial.println("[SD] initialization failed!");
		return;
	}
	Serial.println("[SD] initialization ok");

	Serial.print("[SD] Card type: ");
	switch (card.type())
	{
	case SD_CARD_TYPE_SD1:
		Serial.println("SD1");
		break;
	case SD_CARD_TYPE_SD2:
		Serial.println("SD2");
		break;
	case SD_CARD_TYPE_SDHC:
		Serial.println("SDHC");
		break;
	default:
		Serial.println("Unknown");
	}
	SdVolume volume;
	if (!volume.init(card))
	{
		isStatusOk = false;
		Serial.println("[SD] Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
		return;
	}
	// print the type and size of the first FAT-type volume
	uint32_t volumesize;
	Serial.print("[SD] Volume type is FAT");
	Serial.println(volume.fatType(), DEC);

	volumesize = volume.blocksPerCluster(); // clusters are collections of blocks
	volumesize *= volume.clusterCount();	// we'll have a lot of clusters
	if (volumesize < 8388608ul)
	{
		Serial.print("[SD] Volume size (bytes): ");
		Serial.println(volumesize * 512); // SD card blocks are always 512 bytes
	}
	Serial.print("[SD] Volume size (Kbytes): ");
	volumesize /= 2;
	Serial.println(volumesize);
	Serial.print("[SD] Volume size (Mbytes): ");
	volumesize /= 1024;
	Serial.println(volumesize);

	SdFile root;
	Serial.println("[SD] Files found on the card (name, date and size in bytes): ");
	root.openRoot(volume);

	// list all files in the card with date and size
	root.ls(LS_R | LS_DATE | LS_SIZE);
	root.close();

	if (!SD.begin(BUILTIN_SDCARD))
	{
		isStatusOk = false;
		Serial.println("[SD] initialization failed!");
		return;
	}
	isStatusOk = true;
	Serial.println("[SD] initialization done.");
	listFiles();
	Serial.println("[SD] OK");
}

void TheData::listFiles()
{
	if (!isStatusOk)
		return;
	File root = SD.open("/");
	printDirectory(root, 0);
	Serial.println("[SD] list done");
}

String TheData::on2(uint8_t value)
{
	if(value < 10)
		return "0" + String(value);
	return String(value);
}

void TheData::saveScore(String gamertag, uint16_t points)
{
	if (!isStatusOk)
		return;
	dateTime = now();
	String directory = String(year(dateTime)) + String(on2(month(dateTime))) + String(on2(day(dateTime)));
	if(!SD.exists(directory.c_str()))
	{
		Serial.println("[SD] create directory " + directory);
		SD.mkdir(directory.c_str());
	}
	String filename = directory + "/G" + String(year(dateTime) - 2000) + convertFrom(month(dateTime) - 1) + convertFrom(day(dateTime) - 1) + convertFrom(hour(dateTime)) + convertFrom(minute(dateTime)) + convertFrom(second(dateTime)) + ".txt";
	Serial.println("[SD] " + filename);
	File file = SD.open(filename.c_str(), FILE_WRITE);
	
	if (file)
	{
		file.print(String(year(dateTime)) + String(on2(month(dateTime))) + String(on2(day(dateTime))) + String(on2(hour(dateTime))) 
					+ String(on2(minute(dateTime))) + String(on2(second(dateTime))) 
					+ "|" + gamertag 
					+ "|" + String(points));
		file.close();
	}
	else
	{
		Serial.println("[SD] error writing file");
	}
}
