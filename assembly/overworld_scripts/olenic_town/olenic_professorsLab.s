.thumb
.align 2

.include "../xse_commands.s"
.include "../xse_defines.s"

@ TODO: MapScript_HawthornesLab
@ TODO: Finish Hawthorne pokedex eval
@ TODO: PC somewhere before Rhodanzi for the player to use; make sure it also refers to Hawthorne and not Oak

.global SignScript_OlenicLab_Conservatory
SignScript_OlenicLab_Conservatory:
    msgbox gText_OlenicProfessorsLab_ConservatorySign MSG_SIGN
    end

.global EventScript_OlenicLab_Hawthorne
EventScript_OlenicLab_Hawthorne:
    lock
    faceplayer
    msgbox gText_OlenicProfessorsLab_HawthornePokedexEvaluation MSG_NORMAL
    call Pokedex_Evaluation
    release
    end

.global EventScript_OlenicLab_HawthornesConservatoryAide
EventScript_OlenicLab_HawthornesConservatoryAide:
    @ TODO: Check if player has become champion
    npcchat2 0x2 m_LookDown gText_OlenicProfessorsLab_ConservatoryAide
    end

.global EventScript_OlenicLab_Researcher
EventScript_OlenicLab_Researcher:
    npcchat gText_OlenicProfessorsLab_Researcher
    end
