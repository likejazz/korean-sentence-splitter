#include "sentence_splitter.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(Sentence, ChrLength) {
    ASSERT_EQ(3, kss::getUTF8ChrLength("안", 0));
    ASSERT_EQ(1, kss::getUTF8ChrLength("1", 0));
    ASSERT_EQ(1, kss::getUTF8ChrLength("a", 0));
    ASSERT_EQ(3, kss::getUTF8ChrLength("안녕", 3));
    ASSERT_EQ(1, kss::getUTF8ChrLength("abc", 1));
    ASSERT_EQ(3, kss::getUTF8ChrLength("a반가워", 1));
}

TEST(Sentence, Input) {
    ASSERT_THAT(splitSentences(
            "회사 동료 분들과 다녀왔는데 분위기도 좋고 음식도 맛있었어요 다만, 강남 토끼정이 강남 쉑쉑버거 골목길로 쭉 올라가야 하는데 다들 쉑쉑버거의 유혹에 넘어갈 뻔 했답니다 강남역 맛집 토끼정의 외부 모습."),
                testing::ElementsAre("회사 동료 분들과 다녀왔는데 분위기도 좋고 음식도 맛있었어요",
                                     "다만, 강남 토끼정이 강남 쉑쉑버거 골목길로 쭉 올라가야 하는데 다들 쉑쉑버거의 유혹에 넘어갈 뻔 했답니다",
                                     "강남역 맛집 토끼정의 외부 모습."));
    ASSERT_THAT(splitSentences("역시 토끼정 본 점 답죠?ㅎㅅㅎ 건물은 크지만 간판이 없기 때문에 지나칠 수 있으니 조심하세요 강남 토끼정의 내부 인테리어."),
                testing::ElementsAre("역시 토끼정 본 점 답죠?ㅎㅅㅎ", "건물은 크지만 간판이 없기 때문에 지나칠 수 있으니 조심하세요", "강남 토끼정의 내부 인테리어."));
    ASSERT_THAT(splitSentences("전체적으로 편안하고 아늑한 공간으로 꾸며져 있었습니다ㅎㅎ 한 가지 아쉬웠던 건 조명이 너무 어두워 눈이 침침했던..."),
                testing::ElementsAre("전체적으로 편안하고 아늑한 공간으로 꾸며져 있었습니다ㅎㅎ", "한 가지 아쉬웠던 건 조명이 너무 어두워 눈이 침침했던..."));
    ASSERT_THAT(
            splitSentences("총 5명이서 먹고 싶은 음식 하나씩 골라 다양하게 주문했어요 첫 번째 준비된 메뉴는 토끼정 고로케와 깻잎 불고기 사라다를 듬뿍 올려 먹는 맛있는 밥입니다."),
            testing::ElementsAre("총 5명이서 먹고 싶은 음식 하나씩 골라 다양하게 주문했어요",
                                 "첫 번째 준비된 메뉴는 토끼정 고로케와 깻잎 불고기 사라다를 듬뿍 올려 먹는 맛있는 밥입니다."));
    ASSERT_THAT(splitSentences("다들 엄청 잘 드셨습니다ㅋㅋ 이건 제가 시킨 촉촉한 고로케와 크림스튜우동."),
                testing::ElementsAre("다들 엄청 잘 드셨습니다ㅋㅋ", "이건 제가 시킨 촉촉한 고로케와 크림스튜우동."));
    ASSERT_THAT(splitSentences("와사비를 안 좋아하는 저는 불행인지 다행인지 연어 지라시를 매우 맛있게 먹었습니다ㅋㅋㅋ 다음 메뉴는 달짝지근한 숯불 갈비 덮밥입니다!"),
                testing::ElementsAre("와사비를 안 좋아하는 저는 불행인지 다행인지 연어 지라시를 매우 맛있게 먹었습니다ㅋㅋㅋ", "다음 메뉴는 달짝지근한 숯불 갈비 덮밥입니다!"));
    ASSERT_THAT(splitSentences("(물론 전 안 먹었지만...다른 분들이 그렇다고 하더라구요ㅋㅋㅋㅋㅋㅋㅋ) 마지막 메인 메뉴 양송이 크림수프와 숯불떡갈비 밥입니다."),
                testing::ElementsAre("(물론 전 안 먹었지만...다른 분들이 그렇다고 하더라구요ㅋㅋㅋㅋㅋㅋㅋ)", "마지막 메인 메뉴 양송이 크림수프와 숯불떡갈비 밥입니다."));
    ASSERT_THAT(splitSentences(
            "크림스튜 우동 만큼이나 대박 맛있습니다...ㅠㅠㅠㅠㅠㅠ (크림 소스면 다 좋아하는 거 절대 아닙니다ㅋㅋㅋㅋㅋㅋ) 강남 토끼정 요리는 다 맛있지만 크림소스 요리를 참 잘하는 거 같네요 요건 물만 마시기 아쉬워 시킨 뉴자몽과 밀키소다 딸기통통!"),
                testing::ElementsAre("크림스튜 우동 만큼이나 대박 맛있습니다...ㅠㅠㅠㅠㅠㅠ", "(크림 소스면 다 좋아하는 거 절대 아닙니다ㅋㅋㅋㅋㅋㅋ)",
                                     "강남 토끼정 요리는 다 맛있지만 크림소스 요리를 참 잘하는 거 같네요", "요건 물만 마시기 아쉬워 시킨 뉴자몽과 밀키소다 딸기통통!"));
    ASSERT_THAT(splitSentences(
            "건물 위치도 강남 대로변에서 조금 떨어져 있어 내부 인테리어처럼 아늑한 느낌도 있었구요ㅎㅎ 기회가 되면 다들 꼭 들러보세요~"),
                testing::ElementsAre("건물 위치도 강남 대로변에서 조금 떨어져 있어 내부 인테리어처럼 아늑한 느낌도 있었구요ㅎㅎ", "기회가 되면 다들 꼭 들러보세요~"));
    ASSERT_THAT(splitSentences(
            "요건 물만 마시기 아쉬워 시킨 뉴자몽과 밀키소다 딸기통통! 유자와 자몽의 맛을 함께 느낄 수 있는 뉴자몽은 상큼함 그 자체였어요. 하치만 저는 딸기통통 밀키소다가 더 맛있었습니다ㅎㅎ"),
                testing::ElementsAre("요건 물만 마시기 아쉬워 시킨 뉴자몽과 밀키소다 딸기통통! 유자와 자몽의 맛을 함께 느낄 수 있는 뉴자몽은 상큼함 그 자체였어요.",
                                     "하치만 저는 딸기통통 밀키소다가 더 맛있었습니다ㅎㅎ"));
    ASSERT_THAT(splitSentences("한다...라고 뭐라고?"),
                testing::ElementsAre("한다...라고 뭐라고?"));
    ASSERT_THAT(splitSentences("한다...라 뭐라고?"),
                testing::ElementsAre("한다...라 뭐라고?"));
    ASSERT_THAT(splitSentences("지금으로서는 이번 사태의 근본적 책임이 일본에 있다는 점과 이로 인해 세계 경제가 피해를 볼 수 있다"),
                testing::ElementsAre("지금으로서는 이번 사태의 근본적 책임이 일본에 있다는 점과 이로 인해 세계 경제가 피해를 볼 수 있다"));
    ASSERT_THAT(splitSentences("기회가 되면 다들 꼭 들러보세요.....!하"),
                testing::ElementsAre("기회가 되면 다들 꼭 들러보세요.....!", "하"));
    ASSERT_THAT(splitSentences("He's sexy 'man' 이다. Yeah!"),
                testing::ElementsAre("He's sexy 'man' 이다.", "Yeah!"));
}

TEST(Sentence, NewFeature) {
    ASSERT_THAT(splitSentences("He's sexy 'man' 이다. Yeah!"),
                testing::ElementsAre("He's sexy 'man' 이다.", "Yeah!"));
}

TEST(Sentence, MapCheck) {
    ASSERT_EQ(kss::map[kss::Stats::YO]["구"], kss::ID::PREV);
    ASSERT_EQ(kss::map[kss::Stats::YO]["꽥"], kss::ID::NONE);
    ASSERT_EQ(kss::map[kss::Stats::COMMON]["ㅋ"], kss::ID::CONT);
}