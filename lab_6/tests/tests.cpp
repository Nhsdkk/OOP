#include <gtest/gtest.h>

#include <filesystem>
#include "../src/npc/BaseNpc.h"
#include "../src/backup/BackupHandler.h"
#include "../src/logger/ConsoleLogger.h"
#include "../src/logger/FileLogger.h"

const inline std::string outLogFileName = "logs1.txt";
const inline std::string backupFileName = "backup.txt";
const inline std::string logResult = "String1\nString2\n";
const inline std::string logInput1 = "String1";
const inline std::string logInput2 = "String2";

const inline std::string killLog = "Squirrel1 of type Squirrel got killed by Thief1 of type Thief\n";

void RemoveIfExists(const std::string& filename){
    if (std::filesystem::exists(filename)) std::filesystem::remove(filename);
}

TEST(BackupLoaderTests, ShouldDumpAndLoadData){
    std::vector<std::shared_ptr<Logger::ILogger>> logger {std::make_shared<Logger::ConsoleLogger>()};

    std::vector<std::shared_ptr<NPC::BaseNpc>> items {
        std::make_shared<NPC::Thief>(Utils::Point<double>(1, 1), 1, "name", false, logger),
        std::make_shared<NPC::Elf>(Utils::Point<double>(2, 3), 2, "name1", false, logger),
        std::make_shared<NPC::Squirrel>(Utils::Point<double>(3, 3), 3, "name2", true, logger)
    };

    Backup::BackupHandler backupHandler(backupFileName);
    backupHandler.Backup(items);

    Backup::BackupHandler backupHandler1(backupFileName);
    auto state = backupHandler1.Load();

    RemoveIfExists(backupFileName);

    EXPECT_EQ(state.size(), items.size());

    for (auto idx = 0; idx < items.size(); ++idx){
        EXPECT_TRUE(*state[idx] == *items[idx]);
    }
}

TEST(ConsoleLoggerTests, ShouldLogCorrectly){
    std::ostringstream oss;
    auto logger = Logger::ConsoleLogger(oss, "name");
    logger.log(logInput1);
    logger.log(logInput2);
    EXPECT_EQ(oss.str(), logResult);
}

TEST(FileLoggerTests, ShouldLogCorrectly){
    {
        auto logger = Logger::FileLogger(outLogFileName, "name");
        logger.log(logInput1);
        logger.log(logInput2);
    }

    std::ifstream file(outLogFileName);

    EXPECT_TRUE(file.good());

    std::string result = Utils::read(file);
    file.close();
    RemoveIfExists(outLogFileName);

    EXPECT_EQ(result, logResult);
}

TEST(VisitorTests, ShouldVisitCorrectly) {
    std::ostringstream oss;
    std::vector<std::shared_ptr<Logger::ILogger>> logger {std::make_shared<Logger::ConsoleLogger>(oss, "name")};

    auto thief = std::make_shared<NPC::Thief>(Utils::Point<double>(1, 1), 5, "Thief1", true, logger);
    auto squirrel = std::make_shared<NPC::Squirrel>(Utils::Point<double>(3, 3), 1, "Squirrel1", true, logger);

    thief->accept(squirrel);
    squirrel->accept(thief);
    EXPECT_EQ(oss.str(), killLog);
}

TEST(VisitorTests, ShouldNotKillIfNotInRange) {
    std::ostringstream oss;
    std::vector<std::shared_ptr<Logger::ILogger>> logger {std::make_shared<Logger::ConsoleLogger>(oss, "name")};

    auto thief = std::make_shared<NPC::Thief>(Utils::Point<double>(1, 1), 1, "Thief1", true, logger);
    auto squirrel = std::make_shared<NPC::Squirrel>(Utils::Point<double>(15, 15), 1, "Squirrel1", true, logger);

    thief->accept(squirrel);
    squirrel->accept(thief);
    EXPECT_EQ(oss.str(), "");
}

TEST(VisitorTests, ShouldNotKillIfNotAlive) {
    std::ostringstream oss;
    std::vector<std::shared_ptr<Logger::ILogger>> logger {std::make_shared<Logger::ConsoleLogger>(oss, "name")};

    auto thief = std::make_shared<NPC::Thief>(Utils::Point<double>(1, 1), 5, "Thief1", false, logger);
    auto squirrel = std::make_shared<NPC::Squirrel>(Utils::Point<double>(2, 2), 5, "Squirrel1", true, logger);

    thief->accept(squirrel);
    squirrel->accept(thief);
    EXPECT_EQ(oss.str(), "");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}