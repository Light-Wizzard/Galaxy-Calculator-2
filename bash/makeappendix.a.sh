#!/bin/bash
#
# Written by Jeffrey Scott Flesher
#
# This script makes a webpage for a Galactic Calculation
#
declare TheLastUpdate; TheLastUpdate="14 January 2020";
#
# Arguments            1          2                     3                           4                  5                                  6
# Run Script File with "Sun Size" "Livable Planet Size" "Number of Trinary Engines" "Radius of Galaxy" "Full File Name: appendix.a.xhtml" "Nth"
#
# ./makeappendix.a.sh "864575.9" "7926.2109" "333" "241828072282107.5071453596951" "appendix.a.xhtml" 66
#
# Localize:             time ./makeappendix.a.sh -l
# Run Test              ./makeappendix.a.sh -t
# Do set Localize Sizes ./makeappendix.a.sh -p
# find . -iname "makeappendix.x.mo" -exec rename makeappendix.x.mo makeappendix.a.mo '{}' \;
# Delete ? in shell?check below
# shell?check -x makeappendix.a.sh
#
# find . -iname "*makeappendix.a.mo*" -exec rename makeappendix.a.mo makeappendix.a.mo '{}' \;
trap "echo Exited!; exit;" SIGINT SIGTERM
#
echo; clear;
#
# FIXME Localize all Prompts
###############################################################################
declare -i ThisPrintNth;          ThisPrintNth=1;                              # Print nth Track to reduce page size: 1=True
declare -i MyTrackNth;            MyTrackNth="${6}";                           # 1=Every Track, 2=Every other, 3=Every 3rd, so on
declare -i DoOnlineCheck;         DoOnlineCheck=0;                             # 1=Check Online Status of this Page Link
declare -i TheLocalizedFilesSafe; TheLocalizedFilesSafe=1;                     # 1=Safe: will not overwrite Localized files
declare -i ThisLocalizeAll;       ThisLocalizeAll=1;                           # 1=True Localize all Files, this can get up to 8 Hours.
declare -i UseFreeGoogleTrans;    UseFreeGoogleTrans=1;                        # 1=True Google Translation cost money
declare UserExternalDomainLink;   UserExternalDomainLink="LightWizzard.com";   # Change for your use. TrinaryUniversity.org
declare UserBaseName;             UserBaseName="trinary-universe";             # Change for your use.
declare TheAuthor;                TheAuthor="Jeffrey Scott Flesher";           # Author Name
###############################################################################
declare TheFullScriptPath;           TheFullScriptPath="$(dirname "$(readlink -f "${0}")")"; # No Ending /
declare -i ThisRunTest;              ThisRunTest=0;                            #
declare -i ThisSimulateTrans;        ThisSimulateTrans=0;                      # 1=True will Simulate trans for localizing
declare -a ThisProgress=( "-" "\\" "|" "/" );                                  #
declare -i ThisProgression=0;                                                  #
declare -a LocalizedID;              LocalizedID=();                           # Localize ID for po file
declare -a LocalizedMSG;             LocalizedMSG=();                          # Localize MSG for po file
declare -a LocalizedComment;         LocalizedComment=();                      # Localize Comment for po file
# Where do I put these files in Misc
declare TheLocalizedBaseFolderName;  TheLocalizedBaseFolderName="localized";   # No slash at end
declare TheLocalizedPathFolderName;  TheLocalizedPathFolderName="locale";      # No slash at end
declare TheLocalizedPath;            TheLocalizedPath="${TheFullScriptPath}/${TheLocalizedBaseFolderName}/${TheLocalizedPathFolderName}/";
declare TheLocalizedDetailsFolder;   TheLocalizedDetailsFolder="details";      # No slash at end
declare TheLocalizedDetailsPath;     TheLocalizedDetailsPath="${TheFullScriptPath}/${TheLocalizedBaseFolderName}/${TheLocalizedDetailsFolder}/";
declare TheDefaultLanguage;          TheDefaultLanguage="en";                  # I wrote this in English so this is a constant
declare ThisLanguage;                ThisLanguage="${TheDefaultLanguage}";     # This is set per language file when making Pages
declare TheLocalizedFile;            TheLocalizedFile="makeappendix.a";        # I use this throughout this script
declare -i ThisRunLocalizer;         ThisRunLocalizer=0;                       # 1=True set by -l
# Multilingual Langage File Path -> from above: declare -r ${TheFullScriptPath}/${TheMiscFolderName}/${TheLocalizedPathFolderName}/localized"
export TEXTDOMAINDIR="${TheLocalizedPath}";
# Multilingual Langage File Name -> from above: declare TheLocalizedFile="makeappendix.a"
export TEXTDOMAIN="${TheLocalizedFile}";
declare -a TheLocalizeLanguageList; TheLocalizeLanguageList=();                #
# TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="en";           # 1. Do not activate the default language
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="de";             # 2. German
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="fr";             # 3. French
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="ja";             # 4. Japanese
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="zh-cn";          # 5. Chinese Simplified
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="zh-tw";          # 6. Chinese Traditional
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="ar";             # 7. Arabic
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="es";             # 8. Spanish
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="ca";             # 9. Catalan
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="da";             # 10. Danish
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="nl";             # 11. Dutch
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="tl";             # 12. Filipino
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="fi";             # 13. Finnish
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="gl";             # 14. Galician
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="el";             # 15. Greek
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="haw";            # 16. Hawaiian
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="he";             # 17. Hebrew
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="hi";             # 18. Hindi
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="hu";             # 19. Hungarian
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="id";             # 20. Indonesian
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="ga";             # 21. Irish
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="it";             # 22. Italian
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="ko";             # 23. Korean
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="ku";             # 24. Kurdish
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="pl";             # 25. Polish
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="pt";             # 26. Portuguese
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="ru";             # 27. Russian
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="gd";             # 28. Scots Gaelic
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="sw";             # 29. Swahili
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="sv";             # 30. Swedish
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="th";             # 31. Thai
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="tr";             # 32. Turkish
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="vi";             # 33. Vietnamese
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="yi";             # 34. Yiddish
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="cy";             # 35. Welsh
TheLocalizeLanguageList[$((${#TheLocalizeLanguageList[@]}))]="zu";             # 36. Zulu
# if you want all of them, it will take a month to translate them for free
# TheLocalizeLanguageList=(af ak ar as ast be bg bn-bd bn-in br bs ca cs csb cy da de el en-gb en-us en-za eo es-ar es-cl es-es es-mx et eu fa ff fi fr fy-nl ga-ie gd gl gu-in he hi-in hr hu hy-am id is it ja kk km kn ko ku lg lij lt lv mai mk ml mr nb-no nl nn-no nso or pa-in pl pt-br pt-pt rm ro ru si sk sl son sq sr sv-se ta ta-lk te th tr uk vi zh-cn zh-tw zu);
###############################################################################
declare -i DoBomb;             DoBomb=0;
declare -i DosetLocalizeSizes; DosetLocalizeSizes=0;
declare -i DoHelp;             DoHelp=0;
# Check Argument Count
if [[ $# -eq 0 ]]; then
    DoHelp=1;
elif [[ $# -eq 1 ]]; then
    if [ "${1}" == "-l" ]; then
        ThisRunLocalizer=1;
    elif [ "${1}" == "-p" ]; then
        DosetLocalizeSizes=1;
    elif [ "${1}" == "-t" ]; then
        echo "Test";
        ThisRunTest=1;
    elif [ "${1}" == "-h" ] || [ "${1}" == "--help" ]; then
        DoHelp=1;
    else
        DoBomb=1;
    fi
elif [[ $# -ne 6 ]]; then
    DoBomb=1;
fi
###############################################################################
cleanText()
{
    if [ $# -ne 1 ]; then echo "LOCALIZE_WRONG_ARGS_PASSED_TO ${FUNCNAME[0]}() @ $(basename "${BASH_SOURCE[0]}") : Line # ${LINENO[0]}"; exit 1; fi
    [[ -z ${1} ]] && { return 1; }
    local cleanThis; cleanThis="${1}";
    # &apos; &#39; &#x27;
    # html    | numeric | hex
    # &lsquo; | &#145;  | &#x91; // for the left/beginning single-quote and
    # &rsquo; | &#146;  | &#x92; // for the right/ending single-quote
    # &#8217; for apostrophe and right single quote
    # &#8216; for left single quote.
    #   < &lt;
    #   > &gt;
    #   " &quot;
    #   & &amp;
    #   ' &#39;

    # cleanThis="<It&#39;s>";
    #
    # cleanThis="${cleanThis/\&#39;/\'}"; # messes up editor
    # shellcheck disable=SC2001
    cleanThis="$( echo "${cleanThis}" | sed "s/\&#39;/'/g" )"; # Fix Apostrophe '
    # shellcheck disable=SC2001
    cleanThis="$( echo "${cleanThis}" | sed 's/\"//g' )"; # Remove quotes
    echo "${cleanThis}";
}
###############################################################################
uncleanText()
{
    if [ $# -ne 1 ]; then echo "LOCALIZE_WRONG_ARGS_PASSED_TO ${FUNCNAME[0]}() @ $(basename "${BASH_SOURCE[0]}") : Line # ${LINENO[0]}"; exit 1; fi
    [[ -z ${1} ]] && { return 1; }
    local cleanThis; cleanThis="${1}";

    # shellcheck disable=SC2001
    cleanThis="$( echo "${cleanThis}" | sed "s/'/\&#39;/g" )"; # Fix Apostrophe '
    echo "${cleanThis}";
}
###############################################################################
declare -i ThisTotalCharacters; ThisTotalCharacters=0;
declare -i ThisTotalWords;      ThisTotalWords=0;
setCharacterWordCount()
{
    # Test Number of arguments else die
    [[ $# -ne 1 ]] && { print_error "LOCALIZE_WRONG_ARGS_PASSED_TO" "Usage: ${FUNCNAME[0]}() 'Status' 'Progress'"; pause_function "$(basename "${BASH_SOURCE[0]}") -> ${FUNCNAME[0]}() : ${LINENO[0]} > ${FUNCNAME[1]}()"; return 1; }
    local myTextString;      myTextString="${1}";
    local ThisOldIFS;        ThisOldIFS="$IFS";
    local -a thisWordsCount; thisWordsCount=();
    local -i thisWC;         thisWC=0;

    if [ -n "${myTextString-}" ]; then
        if [ "${thisWC}" -eq 1 ]; then
            ThisTotalWords+=$( echo "${myTextString}" | wc -w );
        else
            #
            IFS=$" ";
            # shellcheck disable=SC2206
            thisWordsCount=( ${myTextString} );
            ThisTotalWords+=${#thisWordsCount[@]};
        fi
        #
        ThisTotalCharacters+=${#myTextString};
    fi
    #
    IFS="$ThisOldIFS";
}
# END setCharacterWordCount
###############################################################################
# 1: myPrintThis: 1 = Print this to screen
#
setLocalizeSizes()
{
    # Test Number of arguments else die
    [[ $# -ne 1 ]] && { print_error "LOCALIZE_WRONG_ARGS_PASSED_TO" "Usage: ${FUNCNAME[0]}() 'Status' 'Progress'"; pause_function "$(basename "${BASH_SOURCE[0]}") -> ${FUNCNAME[0]}() : ${LINENO[0]} > ${FUNCNAME[1]}()"; return 1; }
    local -i myPrintThis; myPrintThis="${1}";
    local thisPOfile;
    local myLine;
    local ThisOldIFS;     ThisOldIFS="$IFS";
    local -i thisLocalStringIndex; thisLocalStringIndex=0;
    local thisLocalString;
    #
    thisPOfile="${TheLocalizedPath}${TheDefaultLanguage}/${TheDefaultLanguage}.po";
    if [ "${myPrintThis}" -eq 1 ]; then
        printInColor "Working on ${TheDefaultLanguage}" "${ColorBgBlack}" "${ColorFgWhite}" 1;
        printInColor "${thisPOfile}" "${ColorBgBlack}" "${ColorFgWhite}" 1;
        if [ -f "${thisPOfile}" ]; then
            while IFS='' read -r line || [[ -n "${line}" ]]; do
                if [ "${myPrintThis}" -eq 1 ]; then
                   echo -en "\b${ThisProgress[$((ThisProgression++))]}"; [[ ${ThisProgression} -ge 3 ]] && ThisProgression=0;
                fi
                if [[ -n "${line}" ]] && [[ "${line:0:1}" != "#" ]]; then
                    if [ "${line:0:5}" == "msgid" ]; then
                        myLine="$( cleanText "${line:6}" )";
                        #echo "msgid: |${myLine}|"
                        LocalizedID[$((${#LocalizedID[@]}))]="${myLine}";
                    elif [ "${line:0:6}" == "msgstr" ]; then
                        myLine="$( cleanText "${line:7}" )";
                        #echo "msgid: |${myLine}|"
                        LocalizedMSG[$((${#LocalizedMSG[@]}))]="${myLine}";
                        setCharacterWordCount "${myLine}";
                    fi
                fi # END if [[ -n "${line}" ]] && [[ "${line:0:1}" != "#" ]]; then
            done < "${thisPOfile}"
        fi # END if [ -f "${thisPOfile}" ]; then
        for thisLocalStringIndex in "${!LocalizedID[@]}"; do
            #echo "${LocalizedMSG[${thisLocalStringIndex}]}"
            gettext -s "${LocalizedID[${thisLocalStringIndex}]}"
        done # END for thisLocalStringIndex in "${!LocalizedID[@]}"; do
        printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
        printInColor "Total Number of Words: ${ThisTotalWords}" "${ColorBgBlack}" "${ColorFgWhite}" 1;
        printInColor "Total Number of Characters: ${ThisTotalCharacters}" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    else
        ThisTotalWords=0;
        ThisTotalCharacters=0;
        for thisLocalString in "${LocalizedMSG[@]}"; do
            setCharacterWordCount "${thisLocalString}";
        done # END for thisLocalString in "${LocalizedID[@]}"; do
    fi
    #
    #
    IFS="$ThisOldIFS";
}
# END setLocalizeSizes
###############################################################################
# All Functions
#
showDetails() { echo ""; echo "    Last Update: ${TheLastUpdate}"; echo ""; cat "${TheLocalizedDetailsPath}/readme.${TheDefaultLanguage}.txt"; }
showUsage() { showDetails; printf "%s\n %s\n %s\n %s\n %s\n %s\n %s\n %s\n\n" "showUsage: ${0}" "Arguments Localize -l, -h,--help or 6 Arguments" "1: [Sun Size in Miles in Diameter]" "2: [Livable Planet Size in Miles in Diameter]" "3: [Number of Trinary Engines]" "4: [Radius of Galaxy in Miles]" "5: [Full File Name: ${MyOutputFileName}]" "6: [Print Nth Track]" 1>&2; }
# END details
# humanize 123456 = 123,456
# FIXME Localize
humanize() { printf "%'.f" "${1}"; }
# roundit 3 1.123456 = 1.123
roundit() { LC_ALL=C /usr/bin/printf "%.*f" "${1}" "${2}"; }
isOnline() { if ! ping -w5 -c3 "${1}" > /dev/null 2>&1; then sleep 3; if ! ping -w5 -c3 "${1}" > /dev/null 2>&1; then return 1; else return 0; fi else return 0; fi }
# -------------------------------------
declare STACK;
function get_stack()
{
    if [ $# -ne 1 ]; then echo "LOCALIZE_WRONG_ARGS_PASSED_TO ${FUNCNAME[0]}() @ $(basename "${BASH_SOURCE[0]}") : Line # ${LINENO[0]}"; exit 1; fi
    STACK="";
    local i message; message="${1:-""}"
    local stack_size; stack_size=${#FUNCNAME[@]};
    local func;
    local linen;
    local src;
    # to avoid noise we start with 1 to skip the get_stack function
    for (( i=1; i<stack_size; i++ )); do
        func="${FUNCNAME[$i]}"
        [ x"$func" = x ] && func=MAIN;
        linen="${BASH_LINENO[$(( i - 1 ))]}"
        src="${BASH_SOURCE[$i]}"
        [ x"$src" = x ] && src=non_file_source;
        STACK+=$'\n\t'"at: ${func} ${src} ${linen}"
    done
    STACK="${message}${STACK}";
}
# No way to test Path
# Below need to be set Manually
declare -i ThisTmHP;            ThisTmHP=0;                                    # Trinary Marker High Precision: 0 = False, 1 = true
declare -i ThisAutoDate;        ThisAutoDate=0;                                # If 1 = True, 0 = Manual Entry below
# Below are auto set
declare ThisDateThisDay;        ThisDateThisDay="14";                          # Change this String for Day
declare -i ThisDateThisMonth;   ThisDateThisMonth=1;                           # Change this Number for Month
declare ThisDateThisYear;       ThisDateThisYear="2020";                       # Change this String for Year
if [ "${ThisAutoDate}" -eq 1 ]; then
    ThisDateThisDay="$(printf %02d "$(date +%d)")";
    ThisDateThisMonth="$(printf %02d "$(date +%m)")";
    ThisDateThisYear="$(printf %02d "$(date +%Y)")";
fi
declare -a ThisDateMonthArray;  ThisDateMonthArray=("January" "February" "March" "April" "May" "June" "July" "August" "September" "October" "November" "December");
declare ThisDateUpdated;        ThisDateUpdated="${ThisDateThisDay} ${ThisDateMonthArray[((${ThisDateThisMonth} - 1))]} ${ThisDateThisYear}"; # Last Update
declare ThisDateChanged;        ThisDateChanged="${ThisDateThisYear}-$(printf %02d "${ThisDateThisMonth}")-${ThisDateThisDay}";           # Change Date
# Variables
# Trinary Marker 137: Some Scientist like to use a Higher Precision
declare ThisTM;                 ThisTM=0.0;                                    # Trinary Marker:
if [ "${ThisTmHP}" -eq 1 ]; then
    ThisTM="$(bc <<< "scale=13;1 / 137.03599913")";                            # 1/137.03599913 = 0.00729735256683 Note: This has Major Issues
else
    ThisTM="$(bc <<< "scale=13;1 / 137")";                                     # 1/137          = 0.0072992700729  Note: Default Behavior because it works
fi
# Track Number
declare -i ThisTrackNumber;      ThisTrackNumber=0;                            # Counter for loop
# 3 Rings of Magnetic Force Fields
declare ThisRingPlanetSecond;    ThisRingPlanetSecond=0.001;                   # This is based on the Second Ring of the Earth
# 1. Sun Size in miles in diameter
declare MySunSize;
if [ "${ThisRunLocalizer}" -eq 1 ] || [ "${ThisRunTest}" -eq 1 ] || [ "${DoHelp}" -eq 1 ] || [ "${DoBomb}" -eq 1 ]; then
    MySunSize="864575.9";
else
    MySunSize="${1}";                                                          # Default: Our Sun: 864575.9
fi
# 2. Livable Planet Size in miles in diameter
declare MyLivePlanetSize;
if [ "${ThisRunLocalizer}" -eq 1 ] || [ "${ThisRunTest}" -eq 1 ] || [ "${DoHelp}" -eq 1 ] || [ "${DoBomb}" -eq 1 ]; then
    MyLivePlanetSize="7926.2109";
else
    MyLivePlanetSize="${2}";                                                   # Default: Earth 7926.2109
fi
# 3. Trinary Engines
declare -i MyTrinaryEngines;
if [ "${ThisRunLocalizer}" -eq 1 ] || [ "${ThisRunTest}" -eq 1 ] || [ "${DoHelp}" -eq 1 ] || [ "${DoBomb}" -eq 1 ]; then
    MyTrinaryEngines="-333";
else
    MyTrinaryEngines="((-${3}))";                                              # Default Starting number Trinary Engines: -333; Negative for Dark Stars.
fi
declare -i ThisTrackEngines;     ThisTrackEngines="${MyTrinaryEngines}";       # Trinary Engines
# 4. Track Radius
declare MyGalaxyRadius;
if [ "${ThisRunLocalizer}" -eq 1 ] || [ "${ThisRunTest}" -eq 1 ] || [ "${DoHelp}" -eq 1 ] || [ "${DoBomb}" -eq 1 ]; then
    MyGalaxyRadius="241828072282107.5071453596951";
else
    MyGalaxyRadius="${4}";                                                     # based on the size of the Light in parsecs: 241828072282107.5071453596951
fi
# 5. Full Path, File Name and Extension
declare -x MyOutputFileName;
if [ "${ThisRunLocalizer}" -eq 1 ] || [ "${ThisRunTest}" -eq 1 ] || [ "${DoHelp}" -eq 1 ] || [ "${DoBomb}" -eq 1 ]; then
    MyOutputFileName="appendix.a.xhtml";
else
    MyOutputFileName="${5}";                                                   # Default: "appendix.a.xhtml"
fi
# Total number of Tracks: 666 * 2 + 1 since its 0 based: 1333
declare -i ThisTotalTracks;  ThisTotalTracks="(( ((${MyTrinaryEngines#-} * 2) * 2) + 1 ))";
# Atmospheric Pressure Index acts as a Dampener for the Core Frequency causing it to expand at a known Rate based on its Size.
# Livable Planet Ring Frequency: ThisAP is based on Planet Earth, I do not make this an Arguments because I have no way of getting this data
# Torr is a unit of pressure based on an absolute scale defined as 1/760
declare ThisLpDensity;          ThisLpDensity=73.120284;                       # Newtons Constant for Earths Atmospheric Density based on Torr
declare ThisAP; ThisAP="$(roundit 7 "$(bc <<< "scale=9;${ThisLpDensity} * (1/760)")")";  # Earth=0.0962109
declare ThisLpRingFreq; ThisLpRingFreq="$(bc <<< "scale=13;(${MyLivePlanetSize} * ${ThisRingPlanetSecond}) - ${ThisAP}")"; # 7926.2109 * 0.001 = 7.9262109 - ThisAP = 7.830 Hz
# Error Rate
# Based on how much Precession a Sun can have based on its Size Ratio derived by measuring a Top of various sizes
declare ThisCpRate;             ThisCpRate=324.540503;                         # Constant Precession Rate: Constant in Newtons work.
declare ThisPrate; ThisPrate="$(bc <<< "scale=0;${MySunSize}/${ThisCpRate}")"; # Precession Rate: Sun: 10,656 / 4 = 2664
# 2664
declare ThisMaxErrorRate;       ThisMaxErrorRate="${ThisPrate}";               # Precession: you must remove the speed required to over come it.
declare ThisMinErrorRate;       ThisMinErrorRate=0;                            # I adjusted the date as to not need this, but its still required.
declare ThisPI;                 ThisPI=3.14159265359;                          # PI: to use a higher Precession would require recalculate of baseline.
# Iteration Ranges
declare ThisMaxIteration;                                                      # ThisMaxIteration: The longest an Iteration can be
# ThisTM="$(bc <<< "scale=13;1 / 137")";
# MySunSize="864575.9";
# echo "$(bc <<< "scale=0;(${MySunSize} * ${ThisTM}) / 3")";
# 2103
ThisMaxIteration="$(bc <<< "scale=0;(${MySunSize} * ${ThisTM}) / 3")";         # (Diameter in miles) x 1/137 / (3 Phase) = Max Iteration in years
declare ThisAveIteration;                                                      # ThisAveIteration: Based on Suns Magnetic Polarity Reversals
ThisAveIteration="$(bc <<< "scale=0;${ThisMaxIteration} - 91")";               # Sun changes polarity 10-11 (0 - 9) times a Century: 100 - 9 = 91
# 2103-42=2061, what we want is 2103-91=2012, do not confuse End of Time with Average Iteration.
declare ThisMinIteration;                                                      # ThisMinIteration: Based on Max Min of Magnetic Fields from Newton
ThisMinIteration="$(bc <<< "scale=0;${ThisMaxIteration} - 1104")";             # I hard coded date so I did not need Error Rate: Adds down to 6
# 999
declare ThisMaxSpeed;           ThisMaxSpeed=0.0;                              # ThisMaxSpeed: As it begins decent into Galactic Plane
declare ThisMinSpeed;           ThisMinSpeed=0.0;                              # ThisMinSpeed: At its Maximum Amplitude
# Note that there are two ways to get this value; below and using the Livable Planets Properties
#
# List of all Ring Force Fields
#
# Ring-Galaxy-1 = 0.000000000000001
# Ring-Galaxy-2 = 0.00000000000001
# Ring-Galaxy-3 = 0.0000000000001
#
# Ring-Sun-1 = 0.00001
# Ring-Sun-2 = 0.0001
# Ring-Sun-3 = 0.001
#
# Ring-Planet-1 = 0.0001
# Ring-Planet-2 = 0.001
# Ring-Planet-3 = 0.01
#
# Earth for example: Orbital distance in Miles around Sun = 584,000,000 / (365 Days * 24 Hours) = 66,666.666 MPH * 0.0001 = 6.6666666 Hz
# So this is a Double Verification Process; proving that this Math actually works both ways which is Magic proving God Designed this.
declare ThisLpFrequency;        ThisLpFrequency=0.0;                           # Frequency: $ThisMaxSpeed * $ThisRingSunFirst = Frequency of Livable Planet
declare ThisRingSunFirst;       ThisRingSunFirst=0.00001;                      # This is based on the First Ring of the Sun
declare ThisOrbitDist;          ThisOrbitDist=0;                               # Orbital Distance in Miles around the Track.
declare ThisTracFreqMultiplier; ThisTracFreqMultiplier=.0000000000001;         # Track Frequency Multiplier based on Galaxy Ring of Power
declare ThisTrackFreq;          ThisTrackFreq=0.0;                             # Track Frequency: .0000000000001 * ${ThisMinSpeed#-}
declare ThisTabSpace;           ThisTabSpace="    ";                           # Tab Space
declare ThisTableClass;         ThisTableClass='class="normal_center"';        # These are CSS class names used to create the Table
declare ThisRowClass;           ThisRowClass='class="oddlist"';                # These are CSS class names used to create the Table
declare ThisCellClass;          ThisCellClass='class="normal_center"';         # These are CSS class names used to create the Table
declare ThisCellClassCenter;    ThisCellClassCenter='class="normal_center"';   # These are CSS class names used to create the Table
declare ThisCellRightClass;     ThisCellRightClass='class="normal_right"';     # These are CSS class names used to create the Table
declare -i ThisCurNth;          ThisCurNth=0;                                  # Used to iterate
declare -i ThisPrintThat;       ThisPrintThat=1;                               # Used to iterate

declare -i DoNotSkipThis;
if [ "${ThisRunLocalizer}" -eq 1 ] || [ "${ThisRunTest}" -eq 1 ] || [ "${DoHelp}" -eq 1 ] || [ "${DoBomb}" -eq 1 ]; then
    DoNotSkipThis="666";
else
    DoNotSkipThis="$((${3}*2))";                                               # To print Track 666 or Life Track
fi
declare -i ThisPrintedLines;    ThisPrintedLines=0;                            # Number of Printed lines
declare -a ThisTextArray;       ThisTextArray=();                              # Array of Text to Print to Screen and (X)HTML File Format
declare -a ThisTextIDArray;     ThisTextIDArray=();                            # Array of Text to Print to Screen and (X)HTML File Format
declare -a ThisTextLinesArray;  ThisTextLinesArray=();                         # Array of Text to Print to Screen in one line
declare ThisDefinition;         ThisDefinition="";                             # Used to print Definitions
declare ThisTemp;               ThisTemp="";                                   # Used to convert strings
#
# *************************************************************************** #
# 1: Status
# 2: Progress
# printProgress "Running" "total" "myPercent";
# ---------------------------------------
declare -x TermScreenAfter; TermScreenAfter="\033[0J"; # Move to location
declare -x TermLineBefore;  TermLineBefore="\033[1K";  # Erase Current Line
#declare -x TermLineAfter;  TermLineAfter="\033[0K";   # Erase Current Line
declare -x TermUp;          TermUp="\033[1A";          # Move up 1 Line
declare -x TermUpCount;     TermUpCount=2;             #
declare -x TermMessages;    TermMessages="\n";         #
declare -x TermProgress;    TermProgress="";           #
#
# *********************************# tput Background
declare -a ColorsBG; ColorsBG=();
declare -i ColorBgBlack; ColorBgBlack=0;
ColorsBG["${ColorBgBlack}"]="$(tput setab 0)";         # 0: Black ${ColorsBG["${ColorBgBlack}"]}
declare -i ColorBgRed; ColorBgRed=1;
ColorsBG["${ColorBgRed}"]="$(tput setab 1)";           # 1: Red
declare -i ColorBgGreen; ColorBgGreen=2;
ColorsBG["${ColorBgGreen}"]="$(tput setab 2)"          # 2: Green
declare -i ColorBgYellow; ColorBgYellow=3;
ColorsBG["${ColorBgYellow}"]="$(tput setab 3)"         # 3: Yellow
declare -i ColorBgBlue; ColorBgBlue=4;
ColorsBG["${ColorBgBlue}"]="$(tput setab 4)"           # 4: Blue
declare -i ColorBgMagenta; ColorBgMagenta=5;
ColorsBG["${ColorBgMagenta}"]="$(tput setab 5)"        # 5: Magenta
declare -i ColorBgCyan; ColorBgCyan=6;
ColorsBG["${ColorBgCyan}"]="$(tput setab 6)"           # 6: Cyan
declare -i ColorBgWhite; ColorBgWhite=7;
ColorsBG["${ColorBgWhite}"]="$(tput setab 7)"          # 7: White
declare -i ColorBgDefault; ColorBgDefault=9;
ColorsBG["${ColorBgDefault}"]="$(tput setab 9)"        # 9: Default
#
# ******************************** # tput Foreground
declare -a ColorsFG; ColorsFG=();
declare -i ColorFgBlack; ColorFgBlack=0;
ColorsFG["${ColorFgBlack}"]="$(tput setaf 0)";         # 0: Black ${ColorsFG["${ColorFgBlack}"]}
declare -i ColorFgRed; ColorFgRed=1;
ColorsFG["${ColorFgRed}"]="$(tput setaf 1)"            # 1: Red
declare -i ColorFgLightRed; ColorFgLightRed=161;
ColorsFG["${ColorFgLightRed}"]="$(tput setaf 161)"     # 161: Light Red
declare -i ColorFgGreen; ColorFgGreen=2;
ColorsFG["${ColorFgGreen}"]="$(tput setaf 2)"          # 2: Green
declare -i ColorFgLightGreen; ColorFgLightGreen=19;
ColorsFG["${ColorFgLightGreen}"]="$(tput setaf 19)"    # 19: Light Green
declare -i ColorFgYellow; ColorFgYellow=3;
ColorsFG["${ColorFgYellow}"]="$(tput setaf 3)"         # 3: Yellow
declare -i ColorFgLightYellow; ColorFgLightYellow=11;
ColorsFG["${ColorFgLightYellow}"]="$(tput setaf 11)"   # 11: Light Yellow
declare -i ColorFgBlue; ColorFgBlue=4;
ColorsFG["${ColorFgBlue}"]="$(tput setaf 4)"           # 4: Blue
declare -i ColorFgLightBlue; ColorFgLightBlue=12;
ColorsFG["${ColorFgLightBlue}"]="$(tput setaf 12)"     # 12: Light Blue
declare -i ColorFgMagenta; ColorFgMagenta=5;
ColorsFG["${ColorFgMagenta}"]="$(tput setaf 5)"        # 5: Magenta
declare -i ColorFgLightMagenta; ColorFgLightMagenta=13;
ColorsFG["${ColorFgLightMagenta}"]="$(tput setaf 13)"  # 13: Light Magenta
declare -i ColorFgCyan; ColorFgCyan=6;
ColorsFG["${ColorFgCyan}"]="$(tput setaf 6)"           # 6: Cyan
declare -i ColorFgLightCyan; ColorFgLightCyan=14;
ColorsFG["${ColorFgLightCyan}"]="$(tput setaf 14)"     # 14: Light Cyan
declare -i ColorFgWhite; ColorFgWhite=7;
ColorsFG["${ColorFgWhite}"]="$(tput setaf 7)"          # 7: White
declare -i ColorFgLightWhite; ColorFgLightWhite=15;
ColorsFG["${ColorFgLightWhite}"]="$(tput setaf 15)"    # 15: Light White
declare -i ColorFgDefault; ColorFgDefault=9;
ColorsFG["${ColorFgDefault}"]="$(tput setaf 9)"        # 9: Default
#
declare -x T_Reset;                # Reset
# shellcheck disable=SC2034
T_Reset="$(tput sgr0)";
declare -x T_Bold;                 # T_Bold
# shellcheck disable=SC2034
T_Bold="$(tput bold)";
declare -x T_Dim;                  # T_Dim
# shellcheck disable=SC2034
T_Dim="$(tput dim)";
declare -x T_Blink;                # T_Blink
# shellcheck disable=SC2034
T_Blink="$(tput blink)";
declare -x T_Begin_Underline;      # Begin Underline
# shellcheck disable=SC2034
T_Begin_Underline="$(tput smul)";
declare -x T_End_Underline;        # End Underline
# shellcheck disable=SC2034
T_End_Underline="$(tput rmul)";
declare -x T_Reverse;              # Reverse
# shellcheck disable=SC2034
T_Reverse="$(tput rev)";
declare -x T_Begin_Standout;       # Begin Standout
# shellcheck disable=SC2034
T_Begin_Standout="$(tput smso)";
declare -x T_End_Standout;         # End Standout
# shellcheck disable=SC2034
T_End_Standout="$(tput rmso)";
#
declare -x T_Clear_EOL;            # Clear to End of Line
# shellcheck disable=SC2034
T_Clear_EOL="$(tput el)";
declare -x T_Clear_BOL;            # Clear to Beginning of Line
# shellcheck disable=SC2034
T_Clear_BOL="$(tput el1)";
#
if [ "${DoBomb}" -eq 1 ] || [ "${DoHelp}" -eq 1 ]; then
    showUsage; exit 1;
fi
#
if [ "${DosetLocalizeSizes}" -eq 1 ]; then
    echo "Print all Localized Files";
    setLocalizeSizes 1;
    exit 0;
fi
# #############################################################################
# Check input arguments
# Arguments            1          2                     3                           4                  5                                  6
# Run Script File with "Sun Size" "Livable Planet Size" "Number of Trinary Engines" "Radius of Galaxy" "Full File Name: appendix.a.xhtml" "Nth"
# ./makeappendix.a.sh "864575.9" "7926.2109" "333" "241828072282107.5071453596951" "appendix.a.xhtml" 66
if [ "${ThisRunLocalizer}" -eq 0 ] && [ "${ThisRunTest}" -eq 0 ] && [ "${DoHelp}" -eq 0 ] && [ "${DoBomb}" -eq 0 ]; then
    re='^[+-]?[0-9]+([.][0-9]+)?$'
    # Sun Size
    if ! [[ "${1}" =~ $re ]] ; then
       echo "Input 1 (Sun Size: 864575.9): Not a number";
       showUsage; exit 1;
    fi
    # Livable Planet Size
    if ! [[ "${2}" =~ $re ]] ; then
       echo "Input 2 (Livable Planet Size: 7926.2109): Not a number";
       showUsage; exit 1;
    fi
    # Radius of Galaxy
    if ! [[ "${4}" =~ $re ]] ; then
       echo "Input 4 (Radius of Galaxy: 241828072282107.5071453596951): Not a number";
       showUsage; exit 1;
    fi
    # Number of Trinary Engines
    re='^[0-9]+$'
    if ! [[ "${3}" =~ $re ]] ; then
       echo "Input 3 (Number of Trinary Engines: 333): Not a number";
       showUsage; exit 1;
    fi
    # Nth Number
    if ! [[ "${6}" =~ $re ]] ; then
       echo "Input 6 (Number of Nth Lines to Skip Printing): Not a number";
       showUsage; exit 1;
    fi
    # File Name: Lower Case, Alphanumeric, with; - _ .
    re='^[a-z0-9\._-]+(\.[a-z0-9_-]+)?$'
    if ! [[ "${5}" =~ $re ]] ; then
       echo "Input 5 (File Name: ${MyOutputFileName}) Only Alphanumeric, dot (.), underscore (_) and dash (-) are allowed.";
       showUsage; exit 1;
    fi
fi # END if [ "${ThisRunLocalizer}" -eq 0 ] && [ "${ThisRunTest}" -eq 0 ] || [ "${DoHelp}" -eq 0 ] || [ "${DoBomb}" -eq 0 ]; then
###############################################################################
#
# printInColor "Text to Print to Screen" "${ColorBgBlack}" "${ColorFgWhite}"
#
printInColor()
{
    [[ $# -ne 4 ]] && { echo "LOCALIZE_WRONG_ARGS_PASSED_TO Usage: ${FUNCNAME[0]}() 'Text' 'Background Color' 'Foreground Color' $(basename "${BASH_SOURCE[0]}") Line # ${LINENO[0]}"; get_stack "${LINENO[0]}"; echo "${STACK}"; return 1; }
    local myText;       myText="${1}";    #
    local -i myBgColor; myBgColor="${2}"; #
    local -i myFgColor; myFgColor="${3}"; #
    local -i myNewLine; myNewLine="${4}"; #
    #
    if [ "${myNewLine}" -eq 1 ]; then
        echo -e "${T_Clear_BOL}${T_Reset}${ColorsBG[${myBgColor}]}${ColorsFG[${myFgColor}]}${ThisTabSpace}${T_Bold}${myText}${T_Clear_EOL}";
    else
        echo -ne "${T_Clear_BOL}${T_Reset}${ColorsBG[${myBgColor}]}${ColorsFG[${myFgColor}]}${ThisTabSpace}${T_Bold}${myText}${T_Clear_EOL}";
    fi
}
runPrintTest()
{
    printInColor "printInColor Test Black Background with White Foreground"         "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "printInColor Test Black Background with White Foreground"         "${ColorBgBlack}" "${ColorFgRed}" 1;
    printInColor "printInColor Test Black Background with Red Foreground"           "${ColorBgBlack}" "${ColorFgLightRed}" 1;
    printInColor "printInColor Test Black Background with Light Red Foreground"     "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "printInColor Test Black Background with Green Foreground"         "${ColorBgBlack}" "${ColorFgGreen}" 1;
    printInColor "printInColor Test Black Background with Light Green Foreground"   "${ColorBgBlack}" "${ColorFgLightGreen}" 1;
    printInColor "printInColor Test Black Background with Yellow Foreground"        "${ColorBgBlack}" "${ColorFgYellow}" 1;
    printInColor "printInColor Test Black Background with Light Yellow Foreground"  "${ColorBgBlack}" "${ColorFgLightYellow}" 1;
    printInColor "printInColor Test Black Background with Blue Foreground"          "${ColorBgBlack}" "${ColorFgBlue}" 1;
    printInColor "printInColor Test Black Background with Light Blue Foreground"    "${ColorBgBlack}" "${ColorFgLightBlue}" 1;
    printInColor "printInColor Test Black Background with Magenta Foreground"       "${ColorBgBlack}" "${ColorFgMagenta}" 1;
    printInColor "printInColor Test Black Background with Light Magenta Foreground" "${ColorBgBlack}" "${ColorFgLightMagenta}" 1;
    printInColor "printInColor Test Black Background with Cyan Foreground"          "${ColorBgBlack}" "${ColorFgCyan}" 1;
    printInColor "printInColor Test Black Background with LightCyan Foreground"     "${ColorBgBlack}" "${ColorFgLightCyan}" 1;
    printInColor "printInColor Test Black Background with Light White Foreground"   "${ColorBgBlack}" "${ColorFgLightWhite}" 1;
    printInColor "printInColor Test Black Background with Default Foreground"       "${ColorBgBlack}" "${ColorFgDefault}" 1;


    printInColor "printInColor Test White Background with Black Foreground"         "${ColorBgWhite}" "${ColorFgBlack}" 1;
    printInColor "printInColor Test White Background with Red Foreground"           "${ColorBgWhite}" "${ColorFgRed}" 1;
    printInColor "printInColor Test White Background with Light Red Foreground"     "${ColorBgWhite}" "${ColorFgLightRed}" 1;
    printInColor "printInColor Test White Background with Green Foreground"         "${ColorBgWhite}" "${ColorFgGreen}" 1;
    printInColor "printInColor Test White Background with Light Green Foreground"   "${ColorBgWhite}" "${ColorFgLightGreen}" 1;
    printInColor "printInColor Test White Background with Yellow Foreground"        "${ColorBgWhite}" "${ColorFgYellow}" 1;
    printInColor "printInColor Test White Background with Light Yellow Foreground"  "${ColorBgWhite}" "${ColorFgLightYellow}" 1;
    printInColor "printInColor Test White Background with Blue Foreground"          "${ColorBgWhite}" "${ColorFgBlue}" 1;
    printInColor "printInColor Test White Background with Light Blue Foreground"    "${ColorBgWhite}" "${ColorFgLightBlue}" 1;
    printInColor "printInColor Test White Background with Magenta Foreground"       "${ColorBgWhite}" "${ColorFgMagenta}" 1;
    printInColor "printInColor Test White Background with Light Magenta Foreground" "${ColorBgWhite}" "${ColorFgLightMagenta}" 1;
    printInColor "printInColor Test White Background with Cyan Foreground"          "${ColorBgWhite}" "${ColorFgCyan}" 1;
    printInColor "printInColor Test White Background with Light Cyan Foreground"    "${ColorBgWhite}" "${ColorFgLightCyan}" 1;
    printInColor "printInColor Test White Background with Default Foreground"       "${ColorBgWhite}" "${ColorFgDefault}" 1;

    printInColor "printInColor Reset to Black Background with White Foreground"         "${ColorBgBlack}" "${ColorFgWhite}" 1;

}
###############################################################################
#
printProgress()
{
    # Test Number of arguments else die
    [[ $# -ne 3 ]] && { print_error "LOCALIZE_WRONG_ARGS_PASSED_TO" "Usage: ${FUNCNAME[0]}() 'Status' 'Progress'"; pause_function "$(basename "${BASH_SOURCE[0]}") -> ${FUNCNAME[0]}() : ${LINENO[0]} > ${FUNCNAME[1]}()"; return 1; }
    local myMessage;            myMessage="${1}";         # First time must be the Message, after that its blank
    local -i myProgressTotal;   myProgressTotal="${2}";   # Total
    local -i myProgressPercent; myProgressPercent="${3}"; # Current Number
    #
    local thisStatus; thisStatus="[          ] 0%";
    local thisPercentage;
    # ---------------------------------------
    # 1: Command to echo
    # 2: Count
    termReset()
    {
        [[ $# -ne 2 ]] && { print_error "LOCALIZE_WRONG_ARGS_PASSED_TO" "Usage: ${FUNCNAME[0]}() 'Count' 'Terminal Code UP'"; pause_function "$(basename "${BASH_SOURCE[0]}") -> ${FUNCNAME[0]}() : ${LINENO[0]} > ${FUNCNAME[1]}()"; return 1; }
        local myCount; myCount="${2}"
        while (( myCount )); do
            echo -en "${1}";
            (( myCount-- ));
        done
    }
    # ---------------------------------------
    termUpdateStatus()
    {
        # Move Up Number of Lines
        termReset "${TermUp}" "${TermUpCount}";
        # Move to location, Erase Line, and back up
        echo -en "${T_Clear_BOL}${T_Reset}${ColorsBG["${ColorBgBlack}"]}${ColorsBG["${ColorFgGreen}"]}${T_Bold}${TermLineBefore}" "${TermScreenAfter}" "\r";
        #echo -en "${T_Clear_BOL}${TermLineBefore}" "${TermScreenAfter}" "\r";
        # Print Message
        echo -en "${TermMessages}";
        # Print Progress
        echo -e "${T_Clear_BOL}${ThisTabSpace}${TermProgress}${T_Clear_EOL}";
    }
    # ---------------------------------------
    # 1: Message
    termAddMessage()
    {
        [[ $# -ne 1 ]] && { print_error "LOCALIZE_WRONG_ARGS_PASSED_TO" "Usage: ${FUNCNAME[0]}() 'Message'"; pause_function "$(basename "${BASH_SOURCE[0]}") -> ${FUNCNAME[0]}() : ${LINENO[0]} > ${FUNCNAME[1]}()"; return 1; }
        TermMessages+="${ThisTabSpace}${1}\n";
        (( TermUpCount++ ));
    }
    # ---------------------------------------
    # 1: Progress
    termSetProgress()
    {
        [[ $# -ne 1 ]] && { print_error "LOCALIZE_WRONG_ARGS_PASSED_TO" "Usage: ${FUNCNAME[0]}() 'Progress'"; pause_function "$(basename "${BASH_SOURCE[0]}") -> ${FUNCNAME[0]}() : ${LINENO[0]} > ${FUNCNAME[1]}()"; return 1; }
        TermProgress="${1}";
        termUpdateStatus;
    }
    # ---------------------------------------
    # If not empty add a message
    if [[ -n "${myMessage}" ]]; then
        TermUpCount=2;
        TermMessages="\n";
        TermProgress="";
        termAddMessage "${myMessage}";
        termReset "\n" ${TermUpCount};
    fi
    # Make sure you do not divide by 0
    if [ "${myProgressPercent}" -gt 0 ] && [ "${myProgressTotal}" -gt 0 ]; then
        thisCalPercentage="$(bc <<< "scale=1;(${myProgressPercent} / ${myProgressTotal}) * 100")";
        thisPercentage=${thisCalPercentage%.*}
    else
        thisPercentage=0;
    fi
    #
    if [ "${thisPercentage}" -gt 1 ] && [ "${thisPercentage}" -lt 11 ]; then   # 10%
        thisStatus="[#         ] ${thisPercentage}%";
    elif [ "${thisPercentage}" -gt 9 ] && [ "${thisPercentage}" -lt 21 ]; then # 20%
        thisStatus="[##        ] ${thisPercentage}%";
    elif [ "${thisPercentage}" -gt 19 ] && [ "${thisPercentage}" -lt 31 ]; then # 30%
        thisStatus="[###       ] ${thisPercentage}%";
    elif [ "${thisPercentage}" -gt 39 ] && [ "${thisPercentage}" -lt 41 ]; then # 40%
        thisStatus="[####      ] ${thisPercentage}%";
    elif [ "${thisPercentage}" -gt 49 ] && [ "${thisPercentage}" -lt 51 ]; then # 50%
        thisStatus="[#####     ] ${thisPercentage}%";
    elif [ "${thisPercentage}" -gt 59 ] && [ "${thisPercentage}" -lt 61 ]; then # 60%
        thisStatus="[######    ] ${thisPercentage}%";
    elif [ "${thisPercentage}" -gt 69 ] && [ "${thisPercentage}" -lt 71 ]; then # 70%
        thisStatus="[#######   ] ${thisPercentage}%";
    elif [ "${thisPercentage}" -gt 79 ] && [ "${thisPercentage}" -lt 81 ]; then # 80%
        thisStatus="[########  ] ${thisPercentage}%";
    elif [ "${thisPercentage}" -gt 89 ] && [ "${thisPercentage}" -lt 91 ]; then # 90%
        thisStatus="[######### ] ${thisPercentage}%";
    elif [ "${thisPercentage}" -gt 99 ] && [ "${thisPercentage}" -lt 101 ]; then # 100%
        thisStatus="[##########] ${thisPercentage}%";
    fi
    #
    termSetProgress "${thisStatus}";
    #
}
# END printProgress
###############################################################################
# 1. Time in Seconds
sleepFor()
{
    local -i mySleepTotal;     mySleepTotal="${1}";
    local -i thisSleepPercent; thisSleepPercent=0;
    printProgress "Sleeping for ${1} seconds..." "${mySleepTotal}" "${thisSleepPercent}";
    for (( thisSleepPercent=0; thisSleepPercent<mySleepTotal; thisSleepPercent++ )); do
        printProgress "" "${mySleepTotal}" "${thisSleepPercent}";
        sleep 1;
    done
    printProgress "" "${mySleepTotal}" "${mySleepTotal}";
   printInColor "Waking up..." "${ColorBgBlack}" "${ColorFgGreen}" 1;
}
###############################################################################
# use -no-auto to disable autocorrect
localizeIt()
{
    [[ ${ThisRunLocalizer} -eq 0 ]] || [[ "${ThisRunTest}" -eq 1 ]] || [ "${DoHelp}" -eq 1 ] || [ "${DoBomb}" -eq 1 ] && return 0;
    #
    local -i thisSetDebug;         thisSetDebug=0; # 0=No, 1=Yes
    local -i totalLocalized;       totalLocalized="${#LocalizedID[@]}";
    local -i totalLanguages;       totalLanguages="${#TheLocalizeLanguageList[@]}";
    local -i thisLanguagesIndex;   thisLanguagesIndex=0;
    local -i thisLocalStringIndex; thisLocalStringIndex=0;
    local -i toggleThis;           toggleThis=0;
    local -i sleepTime;            sleepTime=0;
    local -i perLineSleep;         perLineSleep=0;
    local -i perFileSleep;         perFileSleep=0;
    local thisPOfile;              thisPOfile="po";
    local thisMOfile;              thisMOfile="mo";
    local thisTrans;               thisTrans="mo-po";
    local -i doTrans;              doTrans=1;
    #
    if [ "${ThisSimulateTrans}" -eq 0 ]; then
        if [ "${UseFreeGoogleTrans}" -eq 1 ]; then
#            perLineSleep=66;   # 60 is 1 Minute, for Free they might cut you off if you make more request then that in 10 Minutes
#            perFileSleep=3666; # 3600 is 1 Hour, for Free this is a very limited amount of characters per hour
            perLineSleep=33;   # 60 is 1 Minute, for Free they might cut you off if you make more request then that in 10 Minutes
            perFileSleep=333; # 3600 is 1 Hour, for Free, this is a very limited amount of characters per hour
        else
            perLineSleep=1; # No delay means Hammer on the Server
            perFileSleep=6;
        fi
    else
        perLineSleep=1;
        perFileSleep=1;
    fi
    if [ ${thisSetDebug} -eq 1 ]; then set -x; fi # Turn On Debug mode
    # http://www.gnu.org/savannah-checkouts/gnu/gettext/manual/html_node/PO-Files.html
    #
    #
    mkdir -p "${TheLocalizedPath}${TheDefaultLanguage}/LC_MESSAGES/";
    #
    echo "# Trinary Galactic Table Translation File"    >  "${TheLocalizedPath}${TheDefaultLanguage}/${TheDefaultLanguage}.po"; # Overwrite
    echo ""                     >>  "${TheLocalizedPath}${TheDefaultLanguage}/${TheDefaultLanguage}.po"; # Appends
    #
    printInColor "Localized total=${totalLocalized}" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    #
    #
    for thisLanguagesIndex in "${!LocalizedID[@]}"; do
        #echo -en "\b${ThisProgress[$((ThisProgression++))]}"; [[ ${ThisProgression} -ge 3 ]] && ThisProgression=0;
        {
            echo "# msgcomment: ${LocalizedComment[$thisLanguagesIndex]}"
            echo "msgid \"${LocalizedID[$thisLanguagesIndex]}\""
            echo "msgstr \"${LocalizedMSG[$thisLanguagesIndex]}\""
            echo ""
        } >> "${TheLocalizedPath}${TheDefaultLanguage}/${TheDefaultLanguage}.po";
    done
    # make mo file
    msgfmt -o "${TheLocalizedPath}${TheDefaultLanguage}/LC_MESSAGES/${TheLocalizedFile}.mo" "${TheLocalizedPath}${TheDefaultLanguage}/${TheDefaultLanguage}.po";
    #
    setLocalizeSizes 0; # set Character and Word Count if we need it
    printInColor "Total Number of Words: ${ThisTotalWords}" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "Total Number of Characters: ${ThisTotalCharacters}" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    #
    if [ "${ThisLocalizeAll}" -eq 1 ]; then
        if hash "trans" 2>/dev/null; then
            #
            for thisLanguagesIndex in "${!TheLocalizeLanguageList[@]}"; do
                doTrans=1;
                thisPOfile="${TheLocalizedPath}${TheLocalizeLanguageList[${thisLanguagesIndex}]}/${TheLocalizeLanguageList[${thisLanguagesIndex}]}.po";
                thisMOfile="${TheLocalizedPath}${TheLocalizeLanguageList[${thisLanguagesIndex}]}/LC_MESSAGES/${TheLocalizedFile}.mo";
                if [ "${TheLocalizedFilesSafe}" -eq 1 ]; then
                    if [ -f "${thisPOfile}" ]; then
                        if [ -f "${thisMOfile}" ]; then
                            doTrans=0;
                        fi
                    fi
                fi # END if [ "${TheLocalizedFilesSafe}" -eq 1 ]; then
                #
                if [ "${doTrans}" -eq 1 ]; then
                    mkdir -p "${TheLocalizedPath}${TheLocalizeLanguageList[${thisLanguagesIndex}]}";
                    mkdir -p "${TheLocalizedPath}${TheLocalizeLanguageList[${thisLanguagesIndex}]}/LC_MESSAGES/";
                    echo "# Trinary Galactic Table Translation File" >  "${thisPOfile}"; # Overwrite
                    echo ""                  >>  "${thisPOfile}"; # Appends
                    for thisLocalStringIndex in "${!LocalizedID[@]}"; do
                        printInColor "Working on ${thisLanguagesIndex} of ${totalLanguages}:  Localizating ${TheLocalizeLanguageList[${thisLanguagesIndex}]}: ${thisLocalStringIndex} of ${totalLocalized}: ${LocalizedID[${thisLocalStringIndex}]}" "${ColorBgBlack}" "${ColorFgBlue}" 1;
                        if [ "${ThisSimulateTrans}" -eq 0 ]; then
                            thisTrans="$( trans -no-autocorrect -no-warn -b -s en -t "${TheLocalizeLanguageList[${thisLanguagesIndex}]}" \""${LocalizedMSG[$thisLocalStringIndex]}"\" )";
                        else
                            thisTrans="${TheLocalizeLanguageList[${thisLanguagesIndex}]}: Simulation of trans";
                        fi
                        thisTrans="$(echo "${thisTrans}" | tr -d '\"' )"; # Remove all quotes, sometimes end quotes is missing or odd number
                        # we do not want to count quotes as not empty
                        if [ "${#thisTrans}" -eq 0 ]; then
                            thisTrans="\"${LocalizedMSG[$thisLocalStringIndex]}\""; # Must be in Quotes
                        else
                            thisTrans="\"${thisTrans}\"";                       # Now add them back, this makes sure the quotes are right
                        fi
                        #
                        printInColor "Trans=|${thisTrans}|" "${ColorBgBlack}" "${ColorFgYellow}" 1;
                        # enclosure for writing files
                        {
                            echo "# msgcomment: ${LocalizedComment[${thisLocalStringIndex}]}"
                            echo "msgid \"${LocalizedID[$thisLocalStringIndex]}\""
                            echo "msgstr ${thisTrans}"
                            echo ""
                        } >> "${thisPOfile}";
                        #
                        if [ "${UseFreeGoogleTrans}" -eq 1 ]; then
                            # I do not want to pound on the Server to translate this, they have kick me off; not sure how long to wait, work in progress...
                            # I have 118 lines so far, so how long do you want to wait, this is per Language,
                            # I have 36 Languages selected; that is 4248 * how many seconds you chose,
                            # at 6 x 4248 = 25,488 seconds / 60 = 424.8 Minutes, / 60 = 7.08 Hours
                            # Google is now Paid only, but you can get a few Free ones,
                            # at over 1 per minute, I have about 118 of them, so that is 118 minutes or almost 2 Hours per file
                            # so adding 2 hours x 118 files = 236 Hours or 9 day
                            # plus the fact we are only getting 1 file with a 1-hour wait so its more like 9 days and 8 hours to get if for free
                            # so I need to make a Progress Bar that reflects this
                            if [ "${ThisSimulateTrans}" -eq 0 ]; then
                                if [ "${toggleThis}" -eq 0 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                elif [ "${toggleThis}" -eq 1 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                elif [ "${toggleThis}" -eq 2 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                elif [ "${toggleThis}" -eq 3 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                elif [ "${toggleThis}" -eq 4 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                elif [ "${toggleThis}" -eq 5 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                elif [ "${toggleThis}" -eq 6 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                elif [ "${toggleThis}" -eq 7 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                elif [ "${toggleThis}" -eq 8 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                elif [ "${toggleThis}" -eq 9 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                elif [ "${toggleThis}" -eq 10 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                elif [ "${toggleThis}" -eq 11 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                elif [ "${toggleThis}" -eq 12 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                elif [ "${toggleThis}" -eq 13 ]; then
                                    sleepTime=$(( perLineSleep + toggleThis ));
                                    toggleThis=0;
                                fi
                            fi # END if [ "${ThisSimulateTrans}" -eq 0 ]; then
                            sleepFor "${sleepTime}";
                            (( toggleThis++ ))
                        fi # END if [ "${UseFreeGoogleTrans}" -eq 1 ]; then
                    done # END for thisLocalStringIndex in "${!LocalizedID[@]}"; do
                    #
                    if [ "${ThisSimulateTrans}" -eq 0 ]; then
                        msgfmt -o "${thisMOfile}" "${thisPOfile}";
                    fi
                    #
                    if [ "${UseFreeGoogleTrans}" -eq 1 ]; then
                        sleepFor "${perFileSleep}"; # 3666 seconds (over an hour per file supported) is an eternity for a Computer, but they limit you per hour, no fails required
                        # this will take 36 x 3,666 = 131,976 or 36.66 Hours to complete, try to push it and you will have trans rejections or untrans strings
                    fi # END if [ "${useFreeGoogleTrans}" -eq 1 ]; then
                fi # END if [ "${doTrans}" -eq 1 ]; then
            done # END for thisLanguagesIndex in "${!TheLocalizeLanguageList[@]}"; do
        else # if hash "trans" 2>/dev/null; then
            printInColor "trans not installed" "${ColorBgBlack}" "${ColorFgRed}" 1;
            printInColor "This Bash Script is not only Localized," "${ColorBgBlack}" "${ColorFgBlue}" 1;
            printInColor "it is self Localizing, it will look up the Translation for every Language you chose," "${ColorBgBlack}" "${ColorFgBlue}" 1;
            printInColor "and create the File for you." "${ColorBgBlack}" "${ColorFgBlue}" 1;
            printInColor "https://github.com/soimort/translate-shell" "${ColorBgBlack}" "${ColorFgYellow}" 1;
            printInColor "You must copy file to Path, you cannot access it from inside another script otherwise." "${ColorBgBlack}" "${ColorFgBlue}" 1;
            printInColor "This downloads the latest file from git" "${ColorBgBlack}" "${ColorFgBlue}" 1;
            printInColor "wget git.io/trans" "${ColorBgBlack}" "${ColorFgYellow}" 1;
            printInColor "this changes Permissions so you can execute it" "${ColorBgBlack}" "${ColorFgBlue}" 1;
            printInColor "chmod +x ./trans" "${ColorBgBlack}" "${ColorFgYellow}" 1;
            printInColor "You can move it to any Folder in your Path, I just use bin, because its the right place to put it." "${ColorBgBlack}" "${ColorFgBlue}" 1;
            printInColor "sudo mv trans /usr/bin/" "${ColorBgBlack}" "${ColorFgYellow}" 1;
        fi # END if hash "trans" 2>/dev/null; then
    fi # END if [ "${ThisLocalizeAll}" -eq 1 ]; then
    if [ "${thisSetDebug}" -eq 1 ]; then set +x; fi # turn OFF debug mode
}
# END localizeIt
###############################################################################
#
# setLocalized "ID" "Text" "Comment";
setLocalized()
{
    if [ $# -ne 3 ]; then echo "LOCALIZE_WRONG_ARGS_PASSED_TO ${FUNCNAME[0]}() @ $(basename "${BASH_SOURCE[0]}") : Line # ${LINENO[0]}"; exit 1; fi
    local thisID;       thisID="${1}";
    local thisText;     thisText="${2}";
    local thisComment;  thisComment="${3}";
    [[ -z ${thisID} ]]      && { echo "LOCALIZE_WRONG_ARGS_NULL thisID"; return 1; }
    [[ -z ${thisText} ]]    && { echo "LOCALIZE_WRONG_ARGS_NULL thisText"; return 1; }
    [[ -z ${thisComment} ]] && { echo "LOCALIZE_WRONG_ARGS_NULL thisComment"; get_stack "${FUNCNAME[0]}"; echo "${STACK}" return 1; }
    #
    ThisTextIDArray[$((${#ThisTextIDArray[@]}))]="${thisID}";
    ThisTextArray[$((${#ThisTextArray[@]}))]="${thisText}";
    LocalizedID[${#LocalizedID[*]}]="${thisID}";
    LocalizedMSG[${#LocalizedMSG[*]}]="${thisText}";
    LocalizedComment[${#LocalizedComment[*]}]="${thisComment}";
}
###############################################################################
print2File()
{
    if [ $# -ne 2 ]; then echo "LOCALIZE_WRONG_ARGS_PASSED_TO ${FUNCNAME[0]}() @ $(basename "${BASH_SOURCE[0]}") : Line # ${LINENO[0]}"; exit 1; fi
    [[ -z ${2} ]] && { return 1; }
    if [ "${ThisRunLocalizer}" -eq 0 ] && [ "${ThisRunTest}" -eq 0 ] && [ "${DoHelp}" -eq 0 ] && [ "${DoBomb}" -eq 0 ]; then
        uncleanText "${1}" >> "${2}";
    fi
}
###############################################################################
#
# 1: Array
# 2: Localized Name
printDefinition()
{
    if [ $# -ne 2 ]; then printf "%s %s \n" "LOCALIZE_WRONG_ARGS_PASSED_TO" "${FUNCNAME[0]}() @ $(basename "${BASH_SOURCE[0]}") : Line # ${LINENO[0]}"; exit 1; fi
    [[ -z ${1} ]] && { return 1; }
    local -n thisArray="$1";
    local thisString;
    [[ -z ${2} ]]    && { printf "%s %s \n" "LOCALIZE_NAME_NOT_SPECIFIED" "${FUNCNAME[0]}(): ${2} @ $(basename "${BASH_SOURCE[0]}") Line # ${LINENO[0]}"; exit 1; }
    # Start Definitions
    print2File "${ThisTabSpace}" "${MyOutputFileName}";

    print2File "${ThisTabSpace}"'<dt><span class="text_code">'"$( gettext -s "${2}" )"'</span></dt>' "${MyOutputFileName}";
    if [ "${ThisRunLocalizer}" -eq 0 ] && [ "${ThisRunTest}" -eq 0 ] && [ "${DoHelp}" -eq 0 ] && [ "${DoBomb}" -eq 0 ]; then
        printInColor "$( gettext -s "${2}" )" "${ColorBgBlack}" "${ColorFgCyan}" 1;
    fi
    print2File "${ThisTabSpace}<dd class=\"small_dd\">" "${MyOutputFileName}";
    for thisText in "${thisArray[@]}"; do
        thisString="$( cleanText "${thisText}" )";
        thisString="$( gettext -s "${thisString}" )";
        if [ "${ThisRunLocalizer}" -eq 0 ] && [ "${ThisRunTest}" -eq 0 ] && [ "${DoHelp}" -eq 0 ] && [ "${DoBomb}" -eq 0 ]; then
            print2File "${ThisTabSpace}${ThisTabSpace}${thisString}<br />" "${MyOutputFileName}";
            printInColor "$( gettext -s "${thisString}" )" "${ColorBgBlack}" "${ColorFgCyan}" 1;
        fi
    done
    print2File "${ThisTabSpace}</dd>" "${MyOutputFileName}";
    if [ "${ThisRunLocalizer}" -eq 0 ] && [ "${ThisRunTest}" -eq 0 ] && [ "${DoHelp}" -eq 0 ] && [ "${DoBomb}" -eq 0 ]; then
        printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    fi
    ThisTextArray=();
    ThisTextLinesArray=();
}
###############################################################################
#
printParagraph()
{
    if [ $# -ne 1 ]; then printf "%s %s \n" "LOCALIZE_WRONG_ARGS_PASSED_TO" "${FUNCNAME[0]}() @ $(basename "${BASH_SOURCE[0]}") : Line # ${LINENO[0]}"; exit 1; fi
    [[ -z ${1} ]] && { return 1; }
    local -n thisArray="${1}";
    local thisString;
    print2File "" "${MyOutputFileName}";
    print2File '<p class="small">' "${MyOutputFileName}";
    for thisText in "${thisArray[@]}"; do
        thisString="$( cleanText "${thisText}" )";
        thisString="$( gettext -s "${thisString}" )"
        if [ "${ThisRunLocalizer}" -eq 0 ] && [ "${ThisRunTest}" -eq 0 ] && [ "${DoHelp}" -eq 0 ] && [ "${DoBomb}" -eq 0 ]; then
            print2File "${ThisTabSpace}${thisString}<br />" "${MyOutputFileName}";
            printInColor "$( gettext -s "${thisString}" )" "${ColorBgBlack}" "${ColorFgMagenta}" 1;
        fi
    done
    print2File "</p>" "${MyOutputFileName}";
    ThisTextArray=();
}
###############################################################################
#
printInputStatus()
{
    if [ $# -ne 1 ]; then printf "%s %s \n" "LOCALIZE_WRONG_ARGS_PASSED_TO" "${FUNCNAME[0]}() @ $(basename "${BASH_SOURCE[0]}") : Line # ${LINENO[0]}"; exit 1; fi
    local -i thisLocalizing; thisLocalizing="${1}";
    # FIXME localize
    ThisTextArray=();
    #
    setLocalized "InputStatus0" "Trinary Matrix Math Galactic Disk Track Table Script is Creating" "InputStatus"; # 0
    setLocalized "InputStatus1" "Last Update" "InputStatus";                                                      # 1
    setLocalized "InputStatus2" "Date Changed" "InputStatus";                                                     # 2
    setLocalized "InputStatus3" "Sun Size" "InputStatus";                                                         # 3
    setLocalized "InputStatus4" "Livable Planet Size" "InputStatus";                                              # 4
    setLocalized "InputStatus5" "Number of Trinary Engines" "InputStatus";                                        # 5
    setLocalized "InputStatus6" "Galaxy Radius" "InputStatus";                                                    # 6
    setLocalized "InputStatus7" "Total number of Tracks in Galaxy" "InputStatus";                                 # 7
    setLocalized "InputStatus8" "Atmospheric Pressure Index" "InputStatus";                                       # 8
    setLocalized "InputStatus9" "miles in Diameter" "InputStatus";                                                # 9
    setLocalized "InputStatus10" "miles" "InputStatus";                                                           # 10
    #
    if [ "${thisLocalizing}" -eq 1 ]; then return 0; fi
    printInColor "###############################################################################" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "######                                                                        #" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "$(printf "###### %s %5s \n" " $( gettext -s "InputStatus0" ):" "#")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "$(printf "###### %s %55s \n" "${MyOutputFileName}" "#")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "$(printf "###### $( gettext -s "InputStatus1" ): %s %42s \n" " ${ThisDateUpdated}" "#")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "$(printf "###### $( gettext -s "InputStatus2" ): %s %47s \n" "${ThisDateChanged}" "#")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "$(printf "###### $( gettext -s "InputStatus3" ): %s %36s \n" "$(humanize "${MySunSize}") $( gettext -s "InputStatus9" )" "#")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "$(printf "###### $( gettext -s "InputStatus4" ): %s %27s \n" "$(humanize "${MyLivePlanetSize}") $( gettext -s "InputStatus9" )" "#")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "$(printf "###### $( gettext -s "InputStatus5" ): %s %41s \n" "$(humanize "${MyTrinaryEngines#-}")" "#")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "$(printf "###### $( gettext -s "InputStatus6" ): %s %31s \n" "$(humanize "${MyGalaxyRadius}") $( gettext -s "InputStatus10" )" "#")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "$(printf "###### $( gettext -s "InputStatus7" ): %s %32s \n" "$(humanize "${ThisTotalTracks}")" "#")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "$(printf "###### $( gettext -s "InputStatus8" ): %s %34s \n" "${ThisAP}" "#")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "######                                                                        #" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "###############################################################################" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    ThisTextArray=();
    # FIXME for testing variables
}
###############################################################################
runPage()
{
    if [ $# -ne 1 ]; then printf "%s %s \n" "LOCALIZE_WRONG_ARGS_PASSED_TO" "${FUNCNAME[0]}() @ $(basename "${BASH_SOURCE[0]}") : Line # ${LINENO[0]}"; exit 1; fi
    local -i thisLocalizing; thisLocalizing="${1}";
    #
    if [ "${thisLocalizing}" -eq 0 ]; then
        # Make sure file exist
        touch "${MyOutputFileName}";
        #  and is empty
        truncate -s 0 "${MyOutputFileName}";
        # now make sure we have Write Permissions to have executed these commands
        if [ ! -f "${MyOutputFileName}" ]; then
            printInColor "Failed to create File: ${MyOutputFileName}" "${ColorBgBlack}" "${ColorFgRed}" 1;
            exit 0;
        fi
    fi
    #
    print2File '<?xml version="1.0" encoding="UTF-8"?>' "${MyOutputFileName}";
    print2File '<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">' "${MyOutputFileName}";
    print2File '<!-- <!DOCTYPE html> -->' "${MyOutputFileName}";
    print2File '<!-- <html lang="en"> -->' "${MyOutputFileName}";
    print2File "<head>" "${MyOutputFileName}";
    # FIXME Localize hearder
    ThisTextArray=();
    #
    ThisTemp='The Principles of the Trinary Universe: Appendix A: Trinary Galactic Track Table';
    setLocalized "Header0" "${ThisTemp}" "Header"; # 0
    #
    ThisTemp="Author: ${TheAuthor}, Principles of Light Wizzard or Wizards like Sir Isaac Newton and Nikola Tesla";
    setLocalized "Header1" "${ThisTemp}" "Header"; # 1
    #
    ThisTemp="Light,Wizzard,Wizard,Newton,Newtonian,Tesla,Franklin,God,Jesus,Bar/Abbas,Darkness,Trinary,Universe,Sanctuary,Physics,Sun,Step,${TheAuthor}";
    setLocalized "Header2" "${ThisTemp}" "Header"; # 2
    #
    ThisTemp="Author: ${TheAuthor}, Principles of Light Wizzard or Wizards like Sir Isaac Newton and Nikola Tesla";
    setLocalized "Header3" "${ThisTemp}" "Header"; # 3
    #
    print2File "${ThisTabSpace}<title>$( gettext -s "Header0" )</title>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta name="viewport" content="width=device-width, initial-scale=1" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta name="author" content="'"${TheAuthor}"'" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta name="created" content="1961-01-14T18:32:33.366699936" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta name="changedby" content="'"${TheAuthor}"'" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta name="changed" content="'"${ThisDateChanged}"'T18:32:58.366666666" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta name="description" content="'"$( gettext -s "Header1" )"'" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta name="keywords" content="'"$( gettext -s "Header2" )"'" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta name="twitter:card" content="summary_large_image" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta name="twitter:site" content="@TheLightWizzard" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta name="twitter:creator" content="@TheLightWizzard" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta name="twitter:title" content="'"$( gettext -s "Header0" )"'" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta name="twitter:description" content="'"$( gettext -s "Header3" )"'" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<meta name="twitter:image" content="images/cover.jpg" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<link rel="shortcut icon" type="image/ico" href="favicon.ico" />' "${MyOutputFileName}";
    #print2File "${ThisTabSpace}"'<link media="amzn-kf8"  rel="Stylesheet" href="kf8.css" />' "${MyOutputFileName}";
    #print2File "${ThisTabSpace}"'<link media="amzn-mobi" rel="Stylesheet" href="mobi.css" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<link rel="stylesheet" href="1doc2rule.min.css" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<!-- <script async="async" src="1doc2rule.min.js"></script> -->' "${MyOutputFileName}";
    print2File "</head>" "${MyOutputFileName}";
    print2File '<body><div class="container">' "${MyOutputFileName}";
    #
    # Title Page
    #
    ThisTextArray=();
    ThisTextLinesArray=();
    # TitlePage0
    setLocalized "TitlePage0" "Appendix A: " "TitlePage";                                             # 0
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=1;
    # TitlePage1
    setLocalized "TitlePage1" "Trinary Galactic Track Table" "TitlePage";                             # 1
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=0;
    # TitlePage2
    setLocalized "TitlePage2" "The Principles of the Trinary Universe" "TitlePage";                   # 2
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=0;
    # TitlePage3
    setLocalized "TitlePage3" "CopyRight and CopyLeft by" "TitlePage";                                # 3;
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=1;
    # TitlePage4
    setLocalized "TitlePage4" "${TheAuthor}" "TitlePage";                                    # 4
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=0;
    # TitlePage5
    setLocalized "TitlePage5" "Medically Retired United States Air Force Staff Sergeant" "TitlePage"; # 5
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=0;
    # TitlePage6
    setLocalized "TitlePage6" "Trinary Galactic Track Table" "TitlePage";                             # 6
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=0;
    #
    ThisTemp="http://${UserExternalDomainLink}/books/${UserBaseName}/the.principles.of.the.trinary.universe.html";
    #
    print2File '<div class="noprint">' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="show_web_page_only"><span class="align_center"><span id="google_translate_element" class="google_translate_element"></span></span></span>' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="bigcenter"><cite>'"$( gettext -s "TitlePage2" )"'</cite></span>' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span id="title_page_appendix_a" class="bigcenter">'"$( gettext -s "TitlePage0" )<br />$( gettext -s "TitlePage1" )"'</span>' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="small_text_line_center"><span class="center_italic">C</span>&#174;<span class="center_italic">pyRight</span> &#38; <span class="center_italic">C</span>&#169;<span class="center_italic">pyLeft</span><br />by</span>' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="a_signature_large_center">'"$( gettext -s "TitlePage4" )"'</span>' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="author_title">&#8220;'"$( gettext -s "TitlePage5" )"'&#8221;</span>' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="center_small">Last Update: <span class="text_mono">'"${ThisDateUpdated}</span></span>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="center_small"><a href="'"${ThisTemp}"'" class="blank_target_link">'"${ThisTemp}"'</a></span>' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<div class="a_line_show_break_html"></div><span class="a_blank_line">&#160;</span>' "${MyOutputFileName}";
    print2File "</div>" "${MyOutputFileName}";
    # Sub Header
    print2File '<div class="page_content"><h3 id="appendix_a" class="a_header">'"$( gettext -s "TitlePage0" )<br />$( gettext -s "TitlePage6" )"'</h3>' "${MyOutputFileName}";
    # Explanation
    print2File "" "${MyOutputFileName}";
    #
    if [ "${DoOnlineCheck}" -eq 1 ] && [ "${thisLocalizing}" -eq 0 ]; then
        printInColor "${ThisTabSpace}Checking to see if Link is Online... ${ThisTemp}" "${ColorBgBlack}" "${ColorFgYellow}" 1;
        if isOnline "${ThisTemp}"; then
            printInColor "Online" "${ColorBgBlack}" "${ColorFgGreen}" 1;
        else
            printInColor "Offline:   " "${ColorBgBlack}" "${ColorFgRed}" 1;
        fi
    fi
    #
    #
    if [ "${thisLocalizing}" -eq 0 ]; then
        printInColor "$(gettext -s "TitlePage2")" "${ColorBgBlack}" "${ColorFgLightBlue}" 1;
        printInColor "$(gettext -s "TitlePage0")  $(gettext -s "TitlePage1")" "${ColorBgBlack}" "${ColorFgLightBlue}" 1;
        printInColor "$(gettext -s "TitlePage3")  $(gettext -s "TitlePage4")" "${ColorBgBlack}" "${ColorFgLightBlue}" 1;
        printInColor "$(gettext -s "TitlePage5")" "${ColorBgBlack}" "${ColorFgLightBlue}" 1;
        printInColor "$(gettext -s "TitlePage6")" "${ColorBgBlack}" "${ColorFgLightBlue}" 1;
    fi
    ThisTextArray=(); # Reset
    if [ "${thisLocalizing}" -eq 0 ]; then
        printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    fi
    # Begin Definitions
    print2File "<dl>" "${MyOutputFileName}";
    #
    # Galaxy
    #
    ThisDefinition="The Trinary Galaxy is based on:";
    setLocalized "Galaxy0" "${ThisDefinition}" "Galaxy";                                       # 0
    ThisTextArray=(); # Reset
    #
    ThisTemp='The Trinary Galaxy is based on a Record Player, the Galactic Plane is the Record or Disk.';
    setLocalized "Galaxy1" "${ThisTemp}" "Galaxy";                                             # 1
    #
    ThisTemp='All the Suns orbit the Galaxy at the Same Rate Like the Record Player Arm, and each Track has its own Speed.';
    setLocalized "Galaxy2" "${ThisTemp}" "Galaxy";                                             # 2
    #
    printDefinition "ThisTextArray" "Galaxy0"; # Galaxy
    #
    # Iteration
    #
    ThisDefinition="An Iteration is a Time Period defined as: ";
    setLocalized "Iteration0" "${ThisDefinition}" "Iteration";                                 # 0
    ThisTextArray=(); # Reset
    #
    ThisTemp='An Iteration is a Time Period defined in years, I will calculate here as Maximum, Average, and Minimum,';
    setLocalized "Iteration1" "${ThisTemp}" "Iteration";                                       # 1
    #
    ThisTemp='these Periods are Labeled using the Zodiac Signs, and use the Julian, Gregorian and Mayan Calendar.';
    setLocalized "Iteration2" "${ThisTemp}" "Iteration";                                       # 2
    #
    printDefinition "ThisTextArray" "Iteration0"; # Iteration
    #
    # Trinary Matrix Mathematics
    #
    ThisDefinition="Trinary Matrix Mathematics is based on:";
    setLocalized "TrinaryMatrixMathematics0" "${ThisDefinition}" "TrinaryMatrixMathematics";   # 0
    ThisTextArray=(); # Reset
    #
    ThisTemp='Trinary Matrix Mathematics is based on a Matrix Table, each row is a Track in the Galactic Disk,';
    setLocalized "TrinaryMatrixMathematics1" "${ThisTemp}" "TrinaryMatrixMathematics";         # 1
    #
    ThisTemp='each column has data about the Sun(s) in the Galaxy that supports Life.';
    setLocalized "TrinaryMatrixMathematics2" "${ThisTemp}" "TrinaryMatrixMathematics";         # 2
    #
    ThisTemp='This is based on known Ranges of Energy that Humans could Survive in.';
    setLocalized "TrinaryMatrixMathematics3" "${ThisTemp}" "TrinaryMatrixMathematics";         # 3
    #
    printDefinition "ThisTextArray" "TrinaryMatrixMathematics0"; # TrinaryMatrixMathematics
    #
    # This Trinary Concept Is Based On
    #
    ThisDefinition="This Trinary Concept is Based on:";
    setLocalized "ThisTrinaryConceptIsBasedOn0" "${ThisDefinition}" "ThisTrinaryConceptIsBasedOn"; # 0
    ThisTextArray=(); # Reset
    #
    ThisTemp='The Trinary Concept is one that I came up with myself as a child by age 9,';
    setLocalized "ThisTrinaryConceptIsBasedOn1" "${ThisTemp}" "ThisTrinaryConceptIsBasedOn";   # 1
    #
    ThisTemp='it is based on the Sun having all the Information it needed to know to do its Job in the Galaxy.';
    setLocalized "ThisTrinaryConceptIsBasedOn2" "${ThisTemp}" "ThisTrinaryConceptIsBasedOn";   # 2
    #
    ThisTemp='Once I understood what Sir Isaac Newton was describing,';
    setLocalized "ThisTrinaryConceptIsBasedOn3" "${ThisTemp}" "ThisTrinaryConceptIsBasedOn";   # 3
    #
    ThisTemp='I realized that the Suns Size has everything to do with its Solar System,';
    setLocalized "ThisTrinaryConceptIsBasedOn4" "${ThisTemp}" "ThisTrinaryConceptIsBasedOn";   # 4
    #
    ThisTemp='so I started calculating everything I could: based on its Properties,';
    setLocalized "ThisTrinaryConceptIsBasedOn5" "${ThisTemp}" "ThisTrinaryConceptIsBasedOn";   # 5
    #
    ThisTemp='and wrote this Bash Script to create this XHTML document File that contains this Matrix Table and,';
    ThisTemp="${ThisTemp} I also wrote a Qt Quick QML JavaScript cross platform Open Source Project called galaxy-calculator, link is at bottom of page.";
    setLocalized "ThisTrinaryConceptIsBasedOn6" "${ThisTemp}" "ThisTrinaryConceptIsBasedOn";   # 6
    #
    printDefinition "ThisTextArray" "ThisTrinaryConceptIsBasedOn0"; # ThisTrinaryConceptIsBasedOn
    if [ "${thisLocalizing}" -eq 0 ]; then
        printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    fi
    #
    print2File "</dl>" "${MyOutputFileName}";
    # Input Stats
    ThisTextLinesArray=();
    #
    setLocalized "InputStats0" "Based on a Sun Size of" "InputStats";                          # 0
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=1;
    #
    setLocalized "InputStats1" "miles in Diameter" "InputStats";                               # 1
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=0;
    #
    setLocalized "InputStats2" "Based on" "InputStats";                                        # 2
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=1;
    #
    setLocalized "InputStats3" "Trinary Engines" "InputStats";                                 # 3
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=0;
    #
    setLocalized "InputStats4" "Based on a Galaxy with a Radius of" "InputStats";              # 4
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=1;
    #
    setLocalized "InputStats5" "Total number of Tracks" "InputStats";                          # 5
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=1;
    #
    setLocalized "InputStats6" "Maximum Iteration" "InputStats";                               # 6
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=1;
    #
    setLocalized "InputStats7" "Average Iteration" "InputStats";                               # 7
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=1;
    #
    setLocalized "InputStats8" "Minimum Iteration" "InputStats";                               # 8
    ThisTextLinesArray[$((${#ThisTextLinesArray[@]}))]=1;
    #
    # Based on
    print2File "" "${MyOutputFileName}";
    print2File '<p class="small">' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="text_code">'"$( gettext -s "InputStats0" )"': </span>'"$(humanize "${MySunSize}")"' '"$( gettext -s "InputStats1" )"' <br />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="text_code">'"$( gettext -s "InputStats2" )"': </span>'"$(humanize "${MyTrinaryEngines#-}")"' <span class="text_code">'"$( gettext -s "InputStats3" )"'</span><br />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="text_code">'"$( gettext -s "InputStats4" )"': </span>'"$(humanize "${MyGalaxyRadius}")"' miles<br />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="text_code">'"$( gettext -s "InputStats5" )"': </span>'"$(humanize "${ThisTotalTracks}")" "${MyOutputFileName}";
    print2File "</p>" "${MyOutputFileName}";
    # Iterations
    print2File "" "${MyOutputFileName}";
    print2File '<p class="small">' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="text_code">'"$( gettext -s "InputStats6" )"': </span>'"$(printf "%d" "${ThisMaxIteration}")<br />" "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="text_code">'"$( gettext -s "InputStats7" )"': </span>'"$(printf "%d" "${ThisAveIteration}")<br />" "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="text_code">'"$( gettext -s "InputStats8" )"': </span>'"$(printf "%d" "${ThisMinIteration}")<br />" "${MyOutputFileName}";
    print2File "</p>" "${MyOutputFileName}";
    if [ "${thisLocalizing}" -eq 0 ]; then
        printInColor "$(printf "%s %s %s \n" "$(gettext -s "InputStats0")" "$(humanize "${MySunSize}")" "$(gettext -s "InputStats1")")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
        printInColor "$(printf "%s %s %s \n" "$(gettext -s "InputStats2")" "$(humanize "${MyTrinaryEngines#-}")" "$(gettext -s "InputStats3")")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
        printInColor "$(printf "%s %s \n" "$(gettext -s "InputStats4")" "$(humanize "${MyGalaxyRadius}")")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
        printInColor "$(printf "%s %s \n" "$(gettext -s "InputStats5")" "$(humanize "${ThisTotalTracks}")")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
        printInColor "$(printf "%s %s \n" "$(gettext -s "InputStats6")" "$(printf "%d" "${ThisMaxIteration}")")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
        printInColor "$(printf "%s %s \n" "$(gettext -s "InputStats7")" "$(printf "%d" "${ThisAveIteration}")")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
        printInColor "$(printf "%s %s \n" "$(gettext -s "InputStats8")" "$(printf "%d" "${ThisMinIteration}")")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    fi
    ThisTextArray=();
    # Start Definitions
    print2File "" "${MyOutputFileName}";
    # END of Definitions
    print2File "<dl>" "${MyOutputFileName}";
    if [ "${thisLocalizing}" -eq 0 ]; then
        printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    fi
    #
    # Track
    #
    ThisDefinition="Track:";
    setLocalized "Track0" "${ThisDefinition}" "Track";                                         # 0
    ThisTextArray=(); # Reset
    #
    ThisTemp="Track number of our Galaxy, based on 0 to twice $(("${MyTrinaryEngines#-}" * 2)).";
    setLocalized "Track1" "${ThisTemp}" "Track";                                               # 1
    #
    ThisTemp="Tracks below $(("${MyTrinaryEngines#-}" + 3)) have Negative Trinary Engines because they are Dark Stars,";
    setLocalized "Track2" "${ThisTemp}" "Track";                                               # 2
    #
    ThisTemp='they mix with the Galaxies Force Field Rings, making the numbers Negative Frequencies.';
    setLocalized "Track3" "${ThisTemp}" "Track";                                               # 3
    #
    printDefinition "ThisTextArray" "Track0"; # Track
    #
    # Trinary Engines
    #
    ThisDefinition="Trinary Engines:";
    setLocalized "TrinaryEngines0" "${ThisDefinition}" "TrinaryEngines";                       # 0
    ThisTextArray=(); # Reset
    #
    ThisTemp='Based on how many objects (Planets, Micro Planets, Moons, Asteroids) or Trinary Engines,';
    ThisTemp="${ThisTemp} Trinary Engine in the Table is only referring to Dark Star Companion Stars,";
    ThisTemp="${ThisTemp} they are required to keep the Solar System together,";
    ThisTemp="${ThisTemp} the Dark Energy in these types of Trinary Engines is All Light without Darkness,";
    ThisTemp="${ThisTemp} although Light without Darkness refers to a Spectra of Light not normally in the visible Spectrum Humans can see,";
    ThisTemp="${ThisTemp} without Full Spectrum Technology,";
    ThisTemp="${ThisTemp} these types of Trinary Engine are made of Neutrinos that are Dark in appearance if viewed with Technology,";
    ThisTemp="${ThisTemp} because Technology can not see the Light without Darkness though the Neutron Shell, meaning the outer particles of a Trinary Atom,";
    ThisTemp="${ThisTemp} currently there is no Technology to detect Dark Stars, but Full Spectrum Images can detect their Patterns as Dark Energy.";
    ThisTemp="${ThisTemp} Dark Stars control the Suns or Stars, by creating a network of Dark Energy, ,";
    ThisTemp="${ThisTemp} The Dark Star Companions orbit between Sun in a Solar System that has Planets and Moons, and its Binary counterpart,";
    ThisTemp="${ThisTemp} in our case it is Sirius a Binary Star, as such, the closer a Sun or Star is to the Galaxy, the fewer Trinary Engines it needs to contain it,";
    ThisTemp="${ThisTemp} thus the number of Trinary Engines regulate what Track the Sun also known as a Star is on,";
    ThisTemp="${ThisTemp} thus the farther away from the Galaxy, the more Trinary Engines called Dark Star Companions, it requires to span the distance,";
    ThisTemp="${ThisTemp} in order to contain the other Planets, while the Dark Star maintains the same Rate of Movement at different Speeds.";
    setLocalized "TrinaryEngines1" "${ThisTemp}" "TrinaryEngines";                             # 1
    #
    ThisTemp="Maintaining the same Rate at different Speeds is regulated by the Dark Star itself,";
    ThisTemp="${ThisTemp} and it is in the Galactic Plane, and the Sun also known as Stars pass by it. The Companions job is to keep the solar system together.";
    ThisTemp="${ThisTemp} In the Image I show that the Binary Star Sirius and our Sun are on opposite sides of the Galactic Plane,";
    ThisTemp="${ThisTemp} this is only true when passing through it and coming out of it, as far as I can prove.";
    ThisTemp="${ThisTemp} The Trinary Math Formula for Grafting or Plotting out Alternating Current in a Helix shape waveform,";
    ThisTemp="${ThisTemp} is based on the Frequency that correlates to our Suns interval in terms of time and distance,";
    ThisTemp="${ThisTemp} but due to current Science, the closes Mainstream can estimate is between 30 and 33 Million Years, so I made that a Variable,";
    ThisTemp="${ThisTemp} so it can be adjusted to the correct value, this app is designed to input any Galaxy, thus it does not affect my calculation for when we will Reverse Poles,";
    ThisTemp="${ThisTemp} because that is only a matter of where we are in the Signal itself, and does not even depend on what direction we are heading,";
    ThisTemp="${ThisTemp} meaning into the Galactic Plane, or away from it, it only matters where we are in terms of the Signal itself.";
    ThisTemp="${ThisTemp} I call Gravity a Signal, because God is All Light without Darkness, and is the Force of Gravity in All Newtons Equations, as well as mine,";
    ThisTemp="${ThisTemp} and this is the Gravity that I am calculating for the Galaxy, and its Suns also known as Stars.";
    ThisTemp="${ThisTemp} Dark Stars and their Companions are a special type of Trinary Engine, and like all Trinary Engines, ";
    ThisTemp="${ThisTemp} they are Theoretical, because they can not be proved nor disproved, and stating you must have Faith God Exist,";
    ThisTemp="${ThisTemp} is what Newton said the Bible stated, but that does not make is Science,";
    ThisTemp="${ThisTemp} even Newton said that, instead I state that Trinary Engines emit these Signals that can be Detected by Current Technology,";
    ThisTemp="${ThisTemp} as such I can state they are a Fact in Trinary Science, with Proof using current Technology.";
    ThisTemp="${ThisTemp} To Plot the Data in the Table, I used the following data as variables, Sun Size as 864,575.9 Miles in Diameter,";
    ThisTemp="${ThisTemp} Livable Planet Size as 7926.2109 Miles in Diameter, Number of Trinary Engines as 333 from the Bible,";
    ThisTemp="${ThisTemp} Radius of Galaxy as 241828072282107.5071453596951 Miles, Full File Name: appendix.a.xhtml, and 66 rows to Print,";
    ThisTemp="${ThisTemp} that is for the Bash Script, I have even more control in the Qt App,";
    ThisTemp="${ThisTemp} Trinary Math is Simple, to get the Iterations time period, I only need to know the size of the Sun, ";
    ThisTemp="${ThisTemp} ( 864,575.9 * (1 / 137) ) / 3 = the Maximum year 2103,";
    ThisTemp="${ThisTemp} the Average Iteration is Based on the Suns Magnetic Polarity Reversals, it changes polarity 10 (0 - 9) times a Century: 100 - 9 = 91, thus 2103 - 91 = 2012,";
    ThisTemp="${ThisTemp} to calculate the End of Time, use 42 from the Hitchhikers Guide to the Galaxy, 42 hex is 66 in decimal, and that is from the Bible, and 2103 - 42 = 2061,";
    ThisTemp="${ThisTemp} and Sir Isaac Newton calculated this in the year 2060 under the Julian Calendar, so it is 2061 under the Gregorian Calendar,";
    ThisTemp="${ThisTemp} so this is the Year the Earth should reverse Poles,";
    ThisTemp="${ThisTemp} and I would not take this event Lightly, it is the End of Time also known as the End of Civilization as we know it,";
    ThisTemp="${ThisTemp} so knowing the Size of the Sun is all you need to know, other than the fact that it only works if you start your year at 0,";
    ThisTemp="${ThisTemp} and why the Mayan Calendar starts over after 2012, the tail of the Fish is the year 2060, and why the Gregorian Calendar was introduced,";
    ThisTemp="${ThisTemp} so that it would align with this Bible Code, making Newtons calculation correct,";
    ThisTemp="${ThisTemp} and why the Mayans keep track of time in Iterations of 2012 Years,";
    ThisTemp="${ThisTemp} so the math always works for them, and they knew it would happen after 2012 and before the Fish Tail, which is in the year 2103.";
    setLocalized "TrinaryEngines2" "${ThisTemp}" "TrinaryEngines";                             # 2
    #
    printDefinition "ThisTextArray" "TrinaryEngines0"; # TrinaryEngines
    #
    # Max Speed In MPH
    #
    ThisDefinition="Max Speed in MPH:";
    setLocalized "MaxSpeedInMPH0" "${ThisDefinition}" "MaxSpeedInMPH";                         # 0
    ThisTextArray=(); # Reset
    #
    ThisTemp='Based on the Maximum speed the Sun can travel through the Galactic Plane.';
    setLocalized "MaxSpeedInMPH1" "${ThisTemp}" "MaxSpeedInMPH";                               # 1
    #
    printDefinition "ThisTextArray" "MaxSpeedInMPH0"; # MaxSpeedInMPH
    #
    # Min Speed In MPH
    #
    ThisDefinition="Min Speed in MPH:";
    setLocalized "MinSpeedInMPH0" "${ThisDefinition}" "MinSpeedInMPH";                         # 0
    ThisTextArray=(); # Reset
    #
    ThisTemp='Based on the Minimum speed the Sun can travel after going through the Galactic Plane.';
    setLocalized "MinSpeedInMPH1" "${ThisTemp}" "MinSpeedInMPH";                               # 1
    #
    printDefinition "ThisTextArray" "MinSpeedInMPH0"; # MinSpeedInMPH
    # Frequency In Hz
    #
    ThisDefinition="Frequency in Hz:";
    setLocalized "FrequencyInHz0" "${ThisDefinition}" "FrequencyInHz";                         # 0
    ThisTextArray=(); # Reset
    #
    ThisTemp='Based on the Core Frequency of the Planet, the surface frequencies should be much higher:';
    setLocalized "FrequencyInHz1" "${ThisTemp}" "FrequencyInHz";                               # 1
    #
    ThisTemp="Livable Planet Frequency of $(printf "%0.3f" "${ThisLpRingFreq}") Hz in the year: ${ThisDateThisYear}.";
    setLocalized "FrequencyInHz2" "${ThisTemp}" "FrequencyInHz";                               # 2
    #
    printDefinition "ThisTextArray" "FrequencyInHz0"; # FrequencyInHz
    #
    # Orbital Distance
    #
    ThisDefinition="Orbital Distance:";
    setLocalized "OrbitalDistance0" "${ThisDefinition}" "OrbitalDistance";                     # 0
    ThisTextArray=(); # Reset
    #
    ThisTemp='This is like a Track on a Record, it is the Circumference of the Track in Miles.';
    setLocalized "OrbitalDistance1" "${ThisTemp}" "OrbitalDistance";                           # 1
    #
    printDefinition "ThisTextArray" "OrbitalDistance0"; # OrbitalDistance
    #
    # Track Frequency
    #
    ThisDefinition="Track Frequency in Hz:";
    setLocalized "TrackFrequency0" "${ThisDefinition}" "TrackFrequency";                       # 0
    ThisTextArray=(); # Reset
    #
    ThisTemp='This is based on the Helix shape our Sun travels in around the Galaxy,';
    setLocalized "TrackFrequency1" "${ThisTemp}" "TrackFrequency";                             # 1
    #
    ThisTemp='it also calculates when we pass through the Galactic Plane.';
    setLocalized "TrackFrequency2" "${ThisTemp}" "TrackFrequency";                             # 2
    #
    printDefinition "ThisTextArray" "TrackFrequency0"; # TrackFrequency
    #
    # Life In The Galaxy
    #
    ThisDefinition="Life in the Galaxy is Located:";
    setLocalized "LifeInTheGalaxy0" "${ThisDefinition}" "LifeInTheGalaxy";                     # 0
    ThisTextArray=(); # Reset
    #
    ThisTemp="Currently Life in the Galaxy is on Track *$(("${MyTrinaryEngines#-}" * 2)) ";
    setLocalized "LifeInTheGalaxy1" "${ThisTemp}" "LifeInTheGalaxy";                           # 1
    #
    ThisTemp="If a new Trinary Engine enters or leaves our World or Solar System, we will change tracks.";
    setLocalized "LifeInTheGalaxy2" "${ThisTemp}" "LifeInTheGalaxy";                           # 2
    #
    ThisTemp="After the Polar Shift due in $(("${ThisAveIteration}" + 48)),";
    setLocalized "LifeInTheGalaxy3" "${ThisTemp}" "LifeInTheGalaxy";                           # 3
    #
    ThisTemp="you should start a New Calendar starting with year 0, or continue and use the dates in the Zodiac Table.";
    setLocalized "LifeInTheGalaxy4" "${ThisTemp}" "LifeInTheGalaxy";                           # 4
    #
    ThisTemp="This is the Age of Aquarius, and an Ice Age will Mark its Rain.";
    setLocalized "LifeInTheGalaxy5" "${ThisTemp}" "LifeInTheGalaxy";                           # 5
    #
    printDefinition "ThisTextArray" "LifeInTheGalaxy0"; # LifeInTheGalaxy
    # END Definitions
    print2File "</dl>" "${MyOutputFileName}";
    if [ "${thisLocalizing}" -eq 0 ]; then
        printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    fi
    #
    # Images Of Galaxy
    #
    ThisTemp='If you pick out two Suns on different Tracks across from each other: shown in Red and Green,';
    setLocalized "ImagesOfGalaxy0" "${ThisTemp}" "ImagesOfGalaxy"; # 0
    #
    ThisTemp='and imagined that as I rotated this image simulating the Suns Orbiting the Galaxy,';
    setLocalized "ImagesOfGalaxy1" "${ThisTemp}" "ImagesOfGalaxy"; # 1
    #
    ThisTemp='you would note that all the Suns in the Galaxy stay in line as they orbit it,';
    setLocalized "ImagesOfGalaxy2" "${ThisTemp}" "ImagesOfGalaxy"; # 2
    #
    ThisTemp='this is a poor simulation but it makes my point,';
    setLocalized "ImagesOfGalaxy3" "${ThisTemp}" "ImagesOfGalaxy"; # 3
    #
    ThisTemp='this Math is not the same as it is for the Suns Solar System, so Kepler&#39;s and Newton&#39;s Laws and Math will not help you here, but Trinary Math will.';
    setLocalized "ImagesOfGalaxy4" "${ThisTemp}" "ImagesOfGalaxy"; # 4
    #
    ThisTemp='Trinary Math that I created at age 9 works to solve this problem the Galaxies presented,';
    ThisTemp="${ThisTemp} using the Logic: Speed = Distance/Time, and Distance = Speed * Time,";
    ThisTemp="${ThisTemp} so Speed and Distance are Relative to Frequency, such that: Frequency = 1/Time and Time = 1/Frequency,";
    ThisTemp="${ThisTemp} such that: Frequency (Hz) = Speed of Light (Distance @ 670,616,629 mph * 1 hour; ~ Frequency in miles in 1 Hour or Time) / Wavelength in Miles,";
    ThisTemp="${ThisTemp} using Mainstream estimate of 500,000 Miles an hour for 250,000,000 years, is a distance of 1,095,000,000,000,000,000 miles,";
    ThisTemp="${ThisTemp} using my Formula I get 1,011,954,093,357,316,200 miles, so close enough over that far of a distance.";
    ThisTemp="${ThisTemp} Trinary Science is based on all Energy coming from the Light of God inside every Trinary Atom, meaning 3 types:";
    ThisTemp="${ThisTemp} Proton, Neutron and Electron in the case of Light,";
    ThisTemp="${ThisTemp} as such, all Trinary Math is based on Electricity.";
    ThisTemp="${ThisTemp} When completed the galaxy-calculator, an Open Source github project,";
    ThisTemp="${ThisTemp} which already calculates this same table, will also graphically plot out the path of the Suns or Stars,";
    ThisTemp="${ThisTemp} as they orbit around the Galaxy, once completed, I will replace the images in this table with those.";
    ThisTemp="${ThisTemp} You have two choices, believe Sir Isaac Newton that God is the Force of Gravity in All his Equations,";
    ThisTemp="${ThisTemp} or you can believe Albert Einstein who Denounced all his Theories in favor of Newtons God as the Force of Gravity,";
    ThisTemp="${ThisTemp} either way I am closer to being right than Mainstream Science, because it is based on a Theory Einstein did not even believe in.";
    ThisTemp="${ThisTemp} In this formula, I add up the Track Frequencies instead of using Sine and Cosine, this is not a Simulator,";
    ThisTemp="${ThisTemp} it calculates all Tracks based on the same Sun, and Livable Planet Size, such that it only works for the Track(s) that supports Life,";
    ThisTemp="${ThisTemp} thus it calculates where Life can exist based on these sizes.";
    setLocalized "ImagesOfGalaxy5" "${ThisTemp}" "ImagesOfGalaxy"; # 5
    #
    printParagraph "ThisTextArray"; # ImagesOfGalaxy
    if [ "${thisLocalizing}" -eq 0 ]; then
        printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    fi
    #
    # Images Galaxy Spinning All Solar Systems
    #
    ThisTemp='The Galaxy Spinning all Solar Systems at the same Rate';
    setLocalized "ImagesGalaxySpinningAllSolarSystems0" "${ThisTemp}" "ImagesGalaxySpinningAllSolarSystems"; # 0
    #
    ThisTemp='The Galaxy Spinning all Solar Systems at the same Rate';
    setLocalized "ImagesGalaxySpinningAllSolarSystems1" "${ThisTemp}" "ImagesGalaxySpinningAllSolarSystems"; # 1
    #
    ThisTemp='The Galaxy Spinning all Solar Systems at the same Rate but not speed';
    setLocalized "ImagesGalaxySpinningAllSolarSystems2" "${ThisTemp}" "ImagesGalaxySpinningAllSolarSystems"; # 2
    #
    setLocalized "ImagesGalaxySpinningAllSolarSystems3" "Full Size" "ImagesGalaxySpinningAllSolarSystems"; # 3
    #
    print2File "" "${MyOutputFileName}";
    print2File '<div class="a_illustration" id="illustration_appendix_a_01">' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="image_wrapper">' "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}"'<img src="images/galaxy.thumbnail.png" alt="'"$( gettext -s "ImagesGalaxySpinningAllSolarSystems0" )"'" style="width: 666px; height: 150px;" /><br />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}"'<img src="images/galaxy-original.thumbnail.png" alt="'"$( gettext -s "ImagesGalaxySpinningAllSolarSystems1" )"'" style="width: 666px; height: 150px;" /><br />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}</span>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="a_caption">'"$( gettext -s "ImagesGalaxySpinningAllSolarSystems2" )"'</span>' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span id="galaxy_appendix_a" class="no_show_pdf"><a class="a_link" href="bix/galaxy_appendix_a.xhtml">'"$( gettext -s "ImagesGalaxySpinningAllSolarSystems3" )"'</a></span>' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span id="galaxy_original_appendix_a" class="no_show_pdf"><a class="a_link" href="bix/galaxy_original_appendix_a.xhtml">'"$( gettext -s "ImagesGalaxySpinningAllSolarSystems3" )"'</a></span>' "${MyOutputFileName}";
    print2File "</div>" "${MyOutputFileName}";
    # Image Alt Tags do not really need to go to screen
    ThisTextArray=();  # ImagesGalaxySpinningAllSolarSystems

    # Helix Pattern
    ThisTemp='Trinary Math is 3 Dimensional Math because its based on Electricity also known as Light, that Newton called God.';
    setLocalized "HelixPattern0" "${ThisTemp}" "HelixPattern"; # 0
    #
    ThisTemp='If you view the Sun as orbiting a Dark Star in the Galactic Plane,';
    setLocalized "HelixPattern1" "${ThisTemp}" "HelixPattern"; # 1
    #
    ThisTemp='and having a Trinary Star Configuration, such that Sirius is our Binary Star,';
    setLocalized "HelixPattern2" "${ThisTemp}" "HelixPattern"; # 2
    #
    ThisTemp='and there is also Dark Star Companions that obit around the Trinary Star Systems (Our Sun, Sirius and a Dark Star).';
    setLocalized "HelixPattern3" "${ThisTemp}" "HelixPattern"; # 3
    #
    ThisTemp='This Table Calculates the Frequency of this Waveform shown in this Illustration';
    setLocalized "HelixPattern4" "${ThisTemp}" "HelixPattern"; # 4
    #
    ThisTemp='as well as the Speeds it travels at as it power dives into the Galactic Plane at Maximum Speed,';
    setLocalized "HelixPattern5" "${ThisTemp}" "HelixPattern"; # 5
    #
    ThisTemp='and how its at Minimum Speed as it gets its farthest in Amplitude before it dives back into the Galactic Plane.';
    setLocalized "HelixPattern6" "${ThisTemp}" "HelixPattern"; # 6
    #
    printParagraph "ThisTextArray"; # HelixPattern
    if [ "${thisLocalizing}" -eq 0 ]; then
        printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    fi
    #
    # Images Of Orbital Path Of Sun
    #
    ThisTemp='Orbital path of Sun around Galaxy one revolution';
    setLocalized "ImagesOfOrbitalPathOfSun0" "${ThisTemp}" "ImagesOfOrbitalPathOfSun"; # 0
    #
    ThisTemp='Orbital path of Sun around Galaxy one complete Orbit';
    setLocalized "ImagesOfOrbitalPathOfSun1" "${ThisTemp}" "ImagesOfOrbitalPathOfSun"; # 1
    #
    ThisTemp='Illustration A2: Complete Orbital path of Sun around Galaxy';
    setLocalized "ImagesOfOrbitalPathOfSun2" "${ThisTemp}" "ImagesOfOrbitalPathOfSun"; # 2
    #
    setLocalized "ImagesOfOrbitalPathOfSun3" "Full Size" "ImagesOfOrbitalPathOfSun";   # 3
    #
    # Image of Galaxy Big Picture of Helix Pattern
    print2File "" "${MyOutputFileName}";
    print2File '<div class="a_illustration" id="illustration_appendix_02">' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="image_wrapper">' "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}"'<img src="images/dark-star-460.thumbnail.png"  alt="'"$( gettext -s "ImagesOfOrbitalPathOfSun0" )"'" style="width: 333px; height: 187px;" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}"'<img src="images/dark-star-1391.thumbnail.png" alt="'"$( gettext -s "ImagesOfOrbitalPathOfSun1" )"'" style="width: 333px; height: 187px;" />' "${MyOutputFileName}";
    print2File "${ThisTabSpace}</span>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span class="a_caption">'"$( gettext -s "ImagesOfOrbitalPathOfSun2" )"'</span>' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span id="dark_star_460_appendix_a" class="no_show_pdf"><a class="a_link" href="bix/dark_star_460_appendix_a.xhtml">'"$( gettext -s "ImagesOfOrbitalPathOfSun3" )"'</a></span>' "${MyOutputFileName}";
    print2File "${ThisTabSpace}"'<span id="dark_star_1391_appendix_a" class="no_show_pdf"><a class="a_link" href="bix/dark_star_1391_appendix_a.xhtml">'"$( gettext -s "ImagesOfOrbitalPathOfSun3" )"'</a></span>' "${MyOutputFileName}";
    print2File "</div>" "${MyOutputFileName}";
    # Image Alt Tags do not really need to go to screen
    ThisTextArray=(); # ImagesOfOrbitalPathOfSun
    #
    # Table Header
    #
    setLocalized "TableHeader0" "Track" "TableHeader";            # 0
    #
    setLocalized "TableHeader1" "Trinary" "TableHeader";          # 1
    #
    setLocalized "TableHeader2" "Engines" "TableHeader";          # 2
    #
    setLocalized "TableHeader3" "Max Speed" "TableHeader";        # 3
    #
    setLocalized "TableHeader4" "in MPH" "TableHeader";           # 4
    #
    setLocalized "TableHeader5" "Min Speed" "TableHeader";        # 5
    #
    setLocalized "TableHeader6" "in MPH" "TableHeader";           # 6
    #
    setLocalized "TableHeader7" "Frequency" "TableHeader";        # 7
    #
    setLocalized "TableHeader8" "in Hz" "TableHeader";            # 8
    #
    setLocalized "TableHeader9" "Orbital Distance" "TableHeader"; # 9
    #
    setLocalized "TableHeader10" "in Miles" "TableHeader";        # 10
    #
    setLocalized "TableHeader11" "Track" "TableHeader";           # 11
    #
    setLocalized "TableHeader12" "Frequency" "TableHeader";       # 12
    #
    print2File "" "${MyOutputFileName}";
    print2File '<div class="a_table" id="table_appendix_a_01">' "${MyOutputFileName}";
    print2File "${ThisTabSpace}<table ${ThisTableClass}>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}<thead>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<tr ${ThisRowClass}>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<th ${ThisCellClass}>&#160;$( gettext -s "TableHeader0" )</th>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<th ${ThisCellClass}>&#160;$( gettext -s "TableHeader1" )<br />$( gettext -s "TableHeader2" )</th>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<th ${ThisCellClass}>&#160;$( gettext -s "TableHeader3" )<br />$( gettext -s "TableHeader4" )</th>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<th ${ThisCellClass}>&#160;$( gettext -s "TableHeader5" )<br />$( gettext -s "TableHeader6" )</th>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<th ${ThisCellClass}>&#160;$( gettext -s "TableHeader7" )<br />$( gettext -s "TableHeader8" )</th>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<th ${ThisCellClass}>$( gettext -s "TableHeader9" )<br />$( gettext -s "TableHeader10" )</th>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<th ${ThisCellClass}>$( gettext -s "TableHeader11" )<br />$( gettext -s "TableHeader12" )</th>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}</tr>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}${ThisTabSpace}</thead>" "${MyOutputFileName}";
    #
    if [ "${thisLocalizing}" -eq 0 ]; then
        printInColor "-------------------------------------------------------------------------------------------------------" "${ColorBgBlack}" "${ColorFgLightWhite}" 1;
        printInColor "$(printf "| %s | %s | %10s | %s | %s | %26s |     %s       |\n" "$( gettext -s "TableHeader0" )" "$( gettext -s "TableHeader1" )" "$( gettext -s "TableHeader3" )" "$( gettext -s "TableHeader5" )" "$( gettext -s "TableHeader7" )" "$( gettext -s "TableHeader9" ) " "$( gettext -s "TableHeader11" )")" "${ColorBgBlack}" "${ColorFgLightWhite}" 1;
        printInColor "$(printf "|       | %s | %10s | %9s | %9s | %26s |     %s   |\n" "$( gettext -s "TableHeader2" )" "$( gettext -s "TableHeader4" )" "$( gettext -s "TableHeader6" )" "$( gettext -s "TableHeader8" )" "$( gettext -s "TableHeader10" ) " "$( gettext -s "TableHeader12" )")" "${ColorBgBlack}" "${ColorFgLightWhite}" 1;
        printInColor "-------------------------------------------------------------------------------------------------------" "${ColorBgBlack}" "${ColorFgLightWhite}" 1;
    fi
    #
    ThisTextArray=(); # TableHeader
    # Table Body
    print2File "${ThisTabSpace}${ThisTabSpace}<tbody>" "${MyOutputFileName}";

    if [ "${thisLocalizing}" -eq 0 ]; then
        # Iterate for loop by ThisTrackNumber
        for (( ThisTrackNumber=0; ThisTrackNumber<ThisTotalTracks; ThisTrackNumber++ )); do
            #echo -ne "Working on: (${ThisTrackNumber})\\r";
            # Orbital Distance
            ThisOrbitDist="$(bc <<< "scale=13;((${MyGalaxyRadius} * ${ThisTrackNumber}) * 2) * ${ThisPI} ")";
            ThisOrbitDist="$(printf "%.0f" "${ThisOrbitDist}")";
            # ThisMaxSpeed
            if [ "${ThisTrackEngines}" -le 0 ]; then
                ThisMaxSpeed="$(bc <<< "scale=3;(${ThisAveIteration} * ${ThisTrackEngines}) + ${ThisMaxErrorRate}")";
            else
                ThisMaxSpeed="$(bc <<< "scale=3;(${ThisAveIteration} * ${ThisTrackEngines}) - ${ThisMaxErrorRate}")";
            fi
            # ThisMinSpeed
            # echo "$(bc <<< "scale=3;(999 * 333) - 666")"
            if [ "${ThisTrackEngines}" -le 0 ]; then
                ThisMinSpeed="$(bc <<< "scale=3;(${ThisMinIteration} * ${ThisTrackEngines}) - ${ThisMinErrorRate}")";
            else
                ThisMinSpeed="$(bc <<< "scale=3;(${ThisMinIteration} * ${ThisTrackEngines}) + ${ThisMinErrorRate}")";
            fi
            # ThisLpFrequency
            ThisLpFrequency="$(bc <<< "scale=3;${ThisMaxSpeed} * ${ThisRingSunFirst}")";
            # ThisTrackFreq
            ThisTrackFreq="$(bc <<< "scale=16;${ThisTracFreqMultiplier} * ${ThisMinSpeed#-}")";
            # These Calculations are meaningless
            if [ "${ThisTrackEngines}" == "${MyTrinaryEngines}" ]; then  ThisTrackFreq=0;
            elif [ "${ThisTrackEngines}" == 0 ];  then  ThisTrackFreq=0;
            elif [ "${ThisTrackEngines}" == 1 ];  then  ThisTrackFreq=0;
            elif [ "${ThisTrackEngines}" == -1 ]; then  ThisTrackFreq=0;
            fi
            # Now do the Math
            if [ "${ThisTrackFreq}" == 0 ]; then
                ThisTrackFreq=0;
            else
                ThisTrackFreq="$(bc <<< "scale=16;1/${ThisTrackFreq}")";
            fi
            # Format: Round
            if [ "${ThisTrackEngines}" -le 0 ]; then
                ThisTrackFreq="$(printf "%.0f" "-${ThisTrackFreq}")";
            else
                ThisTrackFreq="$(printf "%.0f" "${ThisTrackFreq}")";
            fi
            #
            if [ "${ThisPrintNth}" -eq 1 ]; then
                (( ThisCurNth++ ))
                if [ "${MyTrackNth}" -eq "${ThisCurNth}" ]; then
                    ThisCurNth=0;
                    ThisPrintThat=1;
                else
                    ThisPrintThat=0;
                fi
                # always show 666 or Life Track
                if [ "${DoNotSkipThis}" -eq "${ThisTrackNumber}" ]; then
                    ThisPrintThat=1;
                fi
            else
                ThisPrintThat=1;
            fi
            #
            if [ "${ThisPrintThat}" -eq 1 ]; then
                # Add Row
                # FIXME Loc
                print2File "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<tr ${ThisRowClass}>" "${MyOutputFileName}";
                if [ "${ThisTrackNumber}" == "$((${MyTrinaryEngines#-} * 2))" ]; then
                    print2File "$(printf "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<td ${ThisCellClassCenter} style=\"font-size: small;\" >*%d</td>\\n" "${ThisTrackNumber}")" "${MyOutputFileName}";
                else
                    print2File "$(printf "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<td ${ThisCellClassCenter} style=\"font-size: small;\">%d</td>\\n" "${ThisTrackNumber}")" "${MyOutputFileName}";
                fi
                ThisTextArray[$((${#ThisTextArray[@]}))]="${ThisTrackNumber}";    # 0

                print2File "$(printf "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<td ${ThisCellRightClass} style=\"font-size: small;\">%d</td>\\n" "${ThisTrackEngines}")" "${MyOutputFileName}";
                ThisTextArray[$((${#ThisTextArray[@]}))]="${ThisTrackEngines}";   # 1

                ThisTemp=$(printf "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<td ${ThisCellRightClass} style=\"font-size: small;\">%'d</td>\\n" "${ThisMaxSpeed}");
                print2File "${ThisTemp}" "${MyOutputFileName}";
                ThisTextArray[$((${#ThisTextArray[@]}))]=$(printf "%'d \\n" "${ThisMaxSpeed}");       # 2

                ThisTemp=$(printf "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<td ${ThisCellRightClass} style=\"font-size: small;\">%'d</td>\\n" "${ThisMinSpeed}");
                print2File "${ThisTemp}" "${MyOutputFileName}";
                ThisTextArray[$((${#ThisTextArray[@]}))]=$(printf "%'d \\n" "${ThisMinSpeed}");       # 3

                print2File "$(printf "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<td ${ThisCellRightClass} style=\"font-size: small;\">%s</td>\\n" "${ThisLpFrequency}")" "${MyOutputFileName}";
                ThisTextArray[$((${#ThisTextArray[@]}))]="${ThisLpFrequency}";      # 4

                ThisTemp=$(printf "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<td ${ThisCellRightClass} style=\"font-size: small;\">%'d</td>\\n" "${ThisOrbitDist}");
                print2File "${ThisTemp}" "${MyOutputFileName}";
                ThisTextArray[$((${#ThisTextArray[@]}))]=$(printf "%'d \\n" "${ThisOrbitDist}");      # 5

                ThisTemp=$(printf "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}<td ${ThisCellRightClass} style=\"font-size: small;\">%'d</td>\\n" "${ThisTrackFreq}");
                print2File "${ThisTemp}" "${MyOutputFileName}";
                ThisTextArray[$((${#ThisTextArray[@]}))]=$(printf "%'d \\n" "${ThisTrackFreq}");      # 6
                print2File "${ThisTabSpace}${ThisTabSpace}${ThisTabSpace}</tr>" "${MyOutputFileName}";
                # FIXME Localization using printf
                # always show 666 or Life Track
                if [ "${DoNotSkipThis}" -eq "${ThisTrackNumber}" ]; then
                    printInColor "$(printf "|*%5d | %7d | %10s | %9s | %9s | %26s | %15s |\n" "${ThisTextArray[0]}" "${ThisTextArray[1]}" "${ThisTextArray[2]}" "${ThisTextArray[3]}" "${ThisTextArray[4]}" "${ThisTextArray[5]}" "${ThisTextArray[6]}")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
                else
                    printInColor "$(printf "| %5d | %7d | %10s | %9s | %9s | %26s | %15s |\n" "${ThisTextArray[0]}" "${ThisTextArray[1]}" "${ThisTextArray[2]}" "${ThisTextArray[3]}" "${ThisTextArray[4]}" "${ThisTextArray[5]}" "${ThisTextArray[6]}")" "${ColorBgBlack}" "${ColorFgWhite}" 1;
                fi
                printInColor "-------------------------------------------------------------------------------------------------------" "${ColorBgBlack}" "${ColorFgLightWhite}" 1;
                ThisTextArray=()
                ((ThisPrintedLines++));
            fi
            # Increment Variables
            ((ThisTrackEngines++)); ((ThisMaxErrorRate++)); ((ThisMinErrorRate++));
        done
        printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    fi # END if [ "${thisLocalizing}" -eq 0 ]; then
    #
    # End of Table
    #
    print2File "${ThisTabSpace}${ThisTabSpace}</tbody>" "${MyOutputFileName}";
    print2File "${ThisTabSpace}</table>" "${MyOutputFileName}";
    #
    print2File "</div>" "${MyOutputFileName}";
    # print2File '<p class="a_blank_line">&#160;</p>' "${MyOutputFileName}";
    # FIXME loc
    ThisTextArray=();
    #
    # TableCaption
    #
    ThisTemp='Table Appendix A: Trinary Matrix Mathematics Galactic Track Table';
    setLocalized "TableCaption0" "${ThisTemp}" "TableCaption"; # 0
    #
    ThisTemp='Usage: (Sun Size in Miles in Diameter) (Livable Planet Size in Miles in Diameter) (Number of Trinary Engines)';
    setLocalized "TableCaption1" "${ThisTemp}" "TableCaption"; # 1
    #
    ThisTemp="(Radius of Galaxy in Miles) (Full File Name: ${MyOutputFileName}) (Nth Number of row to Print)";
    setLocalized "TableCaption2" "${ThisTemp}" "TableCaption"; # 2
    #
    print2File '<div class="a_caption">'"$( gettext -s "TableCaption0" )"'</div>' "${MyOutputFileName}";
    print2File '<p class="small">'"$( gettext -s "TableCaption1" )"'<br />&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;&#160;'"$( gettext -s "TableCaption2" )"'</p>' "${MyOutputFileName}";
    print2File "" "${MyOutputFileName}";
    #
    ThisTextArray=(); # TableCaption
    #
    # Footer
    #
    ThisTemp="./${TheLocalizedFile}.sh 864575.9 7926.2109 333 241828072282107.5071453596951 ${MyOutputFileName} 66";
    setLocalized "Footer0" "${ThisTemp}" "Footer"; # 0
    #
    ThisTemp='This allows you to enter in other Galaxies, and play with different Sun and Planet Sizes.';
    setLocalized "Footer1" "${ThisTemp}" "Footer"; # 1
    #
    ThisTemp='Set ThisPrintNth=1 if you want to only print the nth rows, set trackNth to number to skip,';
    setLocalized "Footer2" "${ThisTemp}" "Footer"; # 2
    #
    ThisTemp='66 gives you about 21 Tracks, setting it to 1 will print all Tracks,';
    setLocalized "Footer3" "${ThisTemp}" "Footer"; # 3
    #
    ThisTemp='set DoNotSkipThis=666 or what ever number you want to see,';
    setLocalized "Footer4" "${ThisTemp}" "Footer"; # 4
    #
    ThisTemp='this saves paper by only printing part of the rows in the table; this is the 6th Argument, I try to limit those.';
    setLocalized "Footer5" "${ThisTemp}" "Footer"; # 5
    #
    ThisTemp='Link to Bash File that created this Page (Save and Set Permissions to run.):';
    setLocalized "Footer6" "${ThisTemp}" "Footer"; # 6
    #
    ThisTemp="If you run the Bash Script like: ./${TheLocalizedFile}.sh or ./${TheLocalizedFile}.sh --help, it will give you Help and more Details."; # 0
    setLocalized "Footer7" "${ThisTemp}" "Footer"; # 7
    #
    printParagraph "ThisTextArray"; # Footer
    #
    if [ "${thisLocalizing}" -eq 0 ]; then
        printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
        # FIXME make a Zip File.

        printInColor "Zipping File: ${TheLocalizedFile}.sh" "${ColorBgBlack}" "${ColorFgWhite}" 1;
        if ! 7z a -tzip "${TheLocalizedFile}.zip" "${TheLocalizedFile}.sh" "${TheLocalizedBaseFolderName}" >/dev/null 2>&1; then
            printInColor "Failed" "${ColorBgBlack}" "${ColorFgRed}" 1;
        fi
        ThisTemp="http://${UserExternalDomainLink}/books/${UserBaseName}/${TheLocalizedFile}.zip";
        if [ "${DoOnlineCheck}" -eq 1 ]; then
            printInColor "${ThisTabSpace}Checking to see if Link is Online... ${ThisTemp}" "${ColorBgBlack}" "${ColorFgWhite}" 1;
            if isOnline "${ThisTemp}"; then
                printInColor "Online" "${ColorBgBlack}" "${ColorFgGreen}" 1;
            else
                printInColor "Offline:   " "${ColorBgBlack}" "${ColorFgRed}" 1;
            fi
        fi
    fi
    print2File '<div class="small"><a href="'"${ThisTemp}"'" class="blank_target_link">'"${ThisTemp}"'</a></div>' "${MyOutputFileName}";
    #
    #
    # Help Command
    #
    ThisTextArray=(); # Clear for HelpCommand
    #
    ThisTemp="http://${UserExternalDomainLink}/books/${UserBaseName}/${TheLocalizedBaseFolderName}/${TheLocalizedDetailsFolder}/readme.${ThisLanguage}.txt";
    #
    if [ "${DoOnlineCheck}" -eq 1 ] && [ "${thisLocalizing}" -eq 0 ]; then
        printInColor "${ThisTabSpace}Checking to see if Link is Online... ${ThisTemp}" "${ColorBgBlack}" "${ColorFgYellow}" 1;
        if isOnline "${ThisTemp}"; then
            printInColor "Online" "${ColorBgBlack}" "${ColorFgGreen}" 1;
        else
            printInColor "Offline:   " "${ColorBgBlack}" "${ColorFgRed}" 1;
        fi
    fi
    #
    print2File '<div class="small"><a href="'"${ThisTemp}"'" class="blank_target_link">'"${ThisTemp}"'</a></div>' "${MyOutputFileName}";
    #
    # Open Source https://github.com/Light-Wizzard/galaxy-calculator
    #
    ThisTemp="https://github.com/Light-Wizzard/galaxy-calculator";
    print2File '<div class="small"><a href="'"${ThisTemp}"'" class="blank_target_link">'"${ThisTemp}"'</a></div>' "${MyOutputFileName}";
    #
    if [ "${thisLocalizing}" -eq 0 ]; then
        print2File "" "${MyOutputFileName}";
        printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    fi
    print2File '</div> <!-- end <div class="page_content"> -->' "${MyOutputFileName}";
    # Footer
    print2File '<div class="show_web_page_only"><span class="footnote"><span class="boxitcenter">' "${MyOutputFileName}";
    print2File '<a class="toc_link" href="appendix.b.xhtml#appendix_b"><span class="green" >&#62; Appendix B</span></a><br /><br />' "${MyOutputFileName}";
    print2File '<a class="toc_link" href="toc.xhtml#toc"><span class="red">Table of Contents</span></a></span><br /><br /></span><span id="debug_info">&#160;</span></div>' "${MyOutputFileName}";
    #
    print2File '<!-- <script>function googleTranslateElementInit() { new google.translate.TranslateElement({pageLanguage: "en", layout: google.translate.TranslateElement.InlineLayout.SIMPLE}, "google_translate_element"); }</script> -->' "${MyOutputFileName}";
    print2File '<!-- <script async="async" src="https://translate.google.com/translate_a/element.js?cb=googleTranslateElementInit"></script> -->' "${MyOutputFileName}";
    print2File '<p class="a_blank_line">&#160;</p>' "${MyOutputFileName}";
    print2File "" "${MyOutputFileName}";
    print2File "</div></body>" "${MyOutputFileName}";
    print2File "</html>" "${MyOutputFileName}";
    # Finished
    if [ "${thisLocalizing}" -eq 0 ]; then
        printInColor "Finished:   " "${ColorBgBlack}" "${ColorFgYellow}" 1;
        printInColor "Printed ${ThisPrintedLines} Tracks: now it is up to you to find out if there is any Life there..." "${ColorBgBlack}" "${ColorFgLightYellow}" 1;
        printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
    fi
}
#
if [ "${ThisRunLocalizer}" -eq 1 ] && [ "${ThisRunTest}" -eq 0 ] && [ "${DoHelp}" -eq 0 ] && [ "${DoBomb}" -eq 0 ]; then
    printInputStatus 1;
    runPage 1;
    localizeIt;
elif [ "${ThisRunLocalizer}" -eq 0 ] &&  [ "${ThisRunTest}" -eq 1 ] && [ "${DoHelp}" -eq 0 ] && [ "${DoBomb}" -eq 0 ]; then
    runPrintTest;
else
    printInputStatus 0;
    runPage 0;
fi
#
printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
printInColor "" "${ColorBgBlack}" "${ColorFgWhite}" 1;
#
###############################################################################
############################### End of File ###################################
