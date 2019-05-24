asn_enc_rval_t s1ap_xer_print_s1ap_initialuemessage(
    asn_app_consume_bytes_f *cb,
    void *app_key,
    s1ap_message *message_p)
{
    S1ap_InitialUEMessageIEs_t *s1ap_InitialUEMessageIEs;
    asn_enc_rval_t er;
    s1ap_InitialUEMessageIEs = &message_p->msg.s1ap_InitialUEMessageIEs;

    cb("<S1ap-InitialUEMessageIEs-PDU>\n", 31, app_key);
    xer_encode_local(&asn_DEF_S1ap_Criticality, &message_p->criticality, cb, app_key, 1);
    xer_encode_local(&asn_DEF_S1ap_ProcedureCode, &message_p->procedureCode, cb, app_key, 1);
    cb("    <S1ap-InitialUEMessageIEs>\n", 31, app_key);
    xer_encode_local(&asn_DEF_S1ap_ENB_UE_S1AP_ID, &s1ap_InitialUEMessageIEs->eNB_UE_S1AP_ID, cb, app_key, 2);
    xer_encode_local(&asn_DEF_S1ap_NAS_PDU, &s1ap_InitialUEMessageIEs->nas_pdu, cb, app_key, 2);
    xer_encode_local(&asn_DEF_S1ap_TAI, &s1ap_InitialUEMessageIEs->tai, cb, app_key, 2);
    xer_encode_local(&asn_DEF_S1ap_EUTRAN_CGI, &s1ap_InitialUEMessageIEs->eutran_cgi, cb, app_key, 2);
    xer_encode_local(&asn_DEF_S1ap_RRC_Establishment_Cause, &s1ap_InitialUEMessageIEs->rrC_Establishment_Cause, cb, app_key, 2);
    /* Optional field */
    if (s1ap_InitialUEMessageIEs->presenceMask & S1AP_INITIALUEMESSAGEIES_S_TMSI_PRESENT)
        xer_encode_local(&asn_DEF_S1ap_S_TMSI, &s1ap_InitialUEMessageIEs->s_tmsi, cb, app_key, 2);
    /* Optional field */
    if (s1ap_InitialUEMessageIEs->presenceMask & S1AP_INITIALUEMESSAGEIES_CSG_ID_PRESENT)
        xer_encode_local(&asn_DEF_S1ap_CSG_Id, &s1ap_InitialUEMessageIEs->csG_Id, cb, app_key, 2);
    /* Optional field */
    if (s1ap_InitialUEMessageIEs->presenceMask & S1AP_INITIALUEMESSAGEIES_GUMMEI_ID_PRESENT)
        xer_encode_local(&asn_DEF_S1ap_GUMMEI, &s1ap_InitialUEMessageIEs->gummei_id, cb, app_key, 2);
    /* Optional field */
    if (s1ap_InitialUEMessageIEs->presenceMask & S1AP_INITIALUEMESSAGEIES_CELLACCESSMODE_PRESENT)
        xer_encode_local(&asn_DEF_S1ap_CellAccessMode, &s1ap_InitialUEMessageIEs->cellAccessMode, cb, app_key, 2);
    /* Optional field */
    if (s1ap_InitialUEMessageIEs->presenceMask & S1AP_INITIALUEMESSAGEIES_GW_TRANSPORTLAYERADDRESS_PRESENT)
        xer_encode_local(&asn_DEF_S1ap_TransportLayerAddress, &s1ap_InitialUEMessageIEs->gW_TransportLayerAddress, cb, app_key, 2);
    /* Optional field */
    if (s1ap_InitialUEMessageIEs->presenceMask & S1AP_INITIALUEMESSAGEIES_RELAYNODE_INDICATOR_PRESENT)
        xer_encode_local(&asn_DEF_S1ap_RelayNode_Indicator, &s1ap_InitialUEMessageIEs->relayNode_Indicator, cb, app_key, 2);
    cb("    </S1ap-InitialUEMessageIEs>\n", 32, app_key);
    cb("</S1ap-InitialUEMessageIEs-PDU>\n", 32, app_key);
    _ASN_ENCODED_OK(er);
}



asn_enc_rval_t s1ap_xer_print_s1ap_uecontextreleaserequest(
    asn_app_consume_bytes_f *cb,
    void *app_key,
    s1ap_message *message_p)
{
    S1ap_UEContextReleaseRequestIEs_t *s1ap_UEContextReleaseRequestIEs;
    asn_enc_rval_t er;
    s1ap_UEContextReleaseRequestIEs = &message_p->msg.s1ap_UEContextReleaseRequestIEs;

    cb("<S1ap-UEContextReleaseRequestIEs-PDU>\n", 38, app_key);
    xer_encode_local(&asn_DEF_S1ap_Criticality, &message_p->criticality, cb, app_key, 1);
    xer_encode_local(&asn_DEF_S1ap_ProcedureCode, &message_p->procedureCode, cb, app_key, 1);
    cb("    <S1ap-UEContextReleaseRequestIEs>\n", 38, app_key);
    xer_encode_local(&asn_DEF_S1ap_MME_UE_S1AP_ID, &s1ap_UEContextReleaseRequestIEs->mme_ue_s1ap_id, cb, app_key, 2);
    xer_encode_local(&asn_DEF_S1ap_ENB_UE_S1AP_ID, &s1ap_UEContextReleaseRequestIEs->eNB_UE_S1AP_ID, cb, app_key, 2);
    xer_encode_local(&asn_DEF_S1ap_Cause, &s1ap_UEContextReleaseRequestIEs->cause, cb, app_key, 2);
    /* Optional field */
    if (s1ap_UEContextReleaseRequestIEs->presenceMask & S1AP_UECONTEXTRELEASEREQUESTIES_GWCONTEXTRELEASEINDICATION_PRESENT)
        xer_encode_local(&asn_DEF_S1ap_GWContextReleaseIndication, &s1ap_UEContextReleaseRequestIEs->gwContextReleaseIndication, cb, app_key, 2);
    cb("    </S1ap-UEContextReleaseRequestIEs>\n", 39, app_key);
    cb("</S1ap-UEContextReleaseRequestIEs-PDU>\n", 39, app_key);
    _ASN_ENCODED_OK(er);
}
