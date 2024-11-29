#include <gtest/gtest.h>

#include <filesystem>
#include "../src/npc/BaseNpc.h"
#include "../src/backup/BackupHandler.h"
#include "../src/logger/ConsoleLogger.h"
#include "../src/logger/FileLogger.h"

const inline std::string outLogFileName = "logs2.txt";
const inline std::string logResult = "String1\nString2\n";
const inline std::string logInput1 = "String1";
const inline std::string logInput2 = "String2";

std::string Read(std::ifstream& file){
    std::string buff;
    std::string result;

    while (std::getline(file, buff)){
        result += buff + '\n';
    }

    return result;
}

void RemoveIfExists(const std::string& filename){
    if (std::filesystem::exists(filename)) std::filesystem::remove(filename);
}

TEST(BackupLoaderTests, ShouldDumpAndLoadData){
    auto logger = std::make_shared<Logger::ConsoleLogger>();

    std::vector<std::shared_ptr<NPC::BaseNpc>> items {
        std::make_shared<NPC::Bear>(Utils::Point<double>(1, 1), Utils::Vec2D<double>(1, 1), "name", false, logger),
        std::make_shared<NPC::Elf>(Utils::Point<double>(2, 3), Utils::Vec2D<double>(1, 1), "name1", false, logger),
        std::make_shared<NPC::Squirrel>(Utils::Point<double>(3, 3), Utils::Vec2D<double>(1, 1), "name2", true, logger)
    };

    Backup::BackupHandler backupHandler;
    backupHandler.Backup(items);
}

TEST(ConsoleLoggerTests, ShouldLogCorrectly){
    std::ostringstream oss;
    auto logger = Logger::ConsoleLogger(oss);
    logger.log(logInput1);
    logger.log(logInput2);
    EXPECT_EQ(oss.str(), logResult);
}

TEST(FileLoggerTests, ShouldLogCorrectly){
    auto logger = Logger::FileLogger(outLogFileName);
    logger.log(logInput1);
    logger.log(logInput2);

    std::ifstream file(outLogFileName);

    EXPECT_TRUE(file.good());

    std::string result = Read(file);
    file.close();
    RemoveIfExists(outLogFileName);

    EXPECT_EQ(result, logResult);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}