#include "charloDonationMessage.h"
#include "customMessages.h"
#include "rando/seed.h"
#include "tp/resource.h"
#include "cxx.h"
#include "main.h"

#ifdef TP_EU
#include "tp/d_s_logo.h"
#endif

#include <cstdint>
#include <cstring>

namespace mod::charlo_donation_message
{
    void createCharloDonationMessage()
    {
        // Get the donation string to use
        using namespace customMessages;
        const MsgEntry* donationEntry;
#ifdef TP_US
        donationEntry = &charloDonationEntryEn;
#elif defined TP_JP
        donationEntry = &charloDonationEntryJp;
#elif defined TP_EU
        switch ( currentLanguage )
        {
            case Languages::uk:
            default:     // The language is invalid/unsupported, so the game defaults to English
            {
                donationEntry = &charloDonationEntryUs;
                break;
            }
            case Languages::de:
            {
                donationEntry = &charloDonationEntryDe;
                break;
            }
            case Languages::fr:
            {
                donationEntry = &charloDonationEntryFr;
                break;
            }
            case Languages::it:
            {
                donationEntry = &charloDonationEntryIt;
                break;
            }
            case Languages::sp:
            {
                donationEntry = &charloDonationEntrySp;
                break;
            }
        }
#endif
        // Allocate memory for the buffer and write the string
        // Must use memcpy instead of strncpy since message commands have NULL characters
        char* buf = new ( sizeof( char ) ) char[donationEntry->size];
        memcpy( buf, donationEntry->msg, donationEntry->size );

        // Assign the buffer
        m_DonationText = buf;
        mod::console << reinterpret_cast<uint32_t>( &m_DonationText ) << "donation \n";
    }
    // clang-format on
}     // namespace mod::charlo_donation_message