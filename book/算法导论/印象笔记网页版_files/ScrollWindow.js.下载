

var _extends = Object.assign || function (target) { for (var i = 1; i < arguments.length; i++) { var source = arguments[i]; for (var key in source) { if (Object.prototype.hasOwnProperty.call(source, key)) { target[key] = source[key]; } } } return target; };

/**
 * Copyright 2015-2016 Evernote Corporation. All rights reserved.
 */
define(['require','react-infinite','react','react-dom','lodash','focus-NotesView-NotesList-Note','focus-NotesView-EmptyState','focus-NotesView-RemindersList-RemindersList','focus-FleChecklist','focusBobFleChecklist','focus-CommEngineCard'],function (require) {
  

  var Infinite = require('react-infinite');
  var React = require('react');
  var ReactDOM = require('react-dom');
  var _ = require('lodash');

  var Note = require('focus-NotesView-NotesList-Note');
  var EmptyState = require('focus-NotesView-EmptyState');
  var RemindersList = require('focus-NotesView-RemindersList-RemindersList');
  var FleChecklist = require('focus-FleChecklist');
  var BobFleChecklist = require('focusBobFleChecklist');
  var CommEngineCard = require('focus-CommEngineCard');
  var BASE_NAME = 'NotesView-ScrollWindow';

  var HEADER_HEIGHTS = {
    ALL_NOTES: 100,
    SEARCH: 197,
    SINGLE_NOTEBOOK_HEADER_COLLAPSED: 98,
    SINGLE_NOTEBOOK_HEADER_EXPANDED: 209,
    TAG: 130
  };
  var MIN_HEADER_SCROLL = {
    DOWN: 240,
    UP: 130
  };
  var NOTE_HEIGHTS = {
    FULL_HEIGHT: 120,
    NO_IMAGES: 96,
    NO_IMAGES_OR_TEXT: 58
  };
  var SCROLL_DELAY = 150;
  var REMINDERS_COLLAPSED_HEIGHT = 43;

  var BANNER_TYPES = {
    NONE: 0,
    SOUTH: 1,
    NORTH: 2,
    TINY: 3
  };
  var BANNER_HEIGHT = 118;
  var BANNER_HEIGHT_TINY = 43;

  /**
   * An Infinite item wrapping a note. Used to differentiate each list item by key, while
   * still pointing to the same note element.
   */
  var NoteListItem = React.createClass({
    displayName: 'NoteListItem',

    propTypes: {
      children: React.PropTypes.element.isRequired
    },

    render: function render() {
      var child = React.Children.only(this.props.children);
      return React.createElement(
        'div',
        null,
        child
      );
    }
  });

  /**
   * The window in which the user can scroll through notes. Also includes the Reminders
   * section above the NotesList.
   */
  var ScrollWindow = React.createClass({
    displayName: 'ScrollWindow',

    propTypes: {
      bannerType: React.PropTypes.number,
      fleChecklistData: React.PropTypes.object,
      bobFleChecklistData: React.PropTypes.object,
      commEngineCardData: React.PropTypes.object,
      isBusiness: React.PropTypes.bool,
      noteInfo: React.PropTypes.objectOf(React.PropTypes.shape({
        allowsDelete: React.PropTypes.bool.isRequired,
        allowsExpunge: React.PropTypes.bool.isRequired,
        allowsReminder: React.PropTypes.bool.isRequired,
        allowsRestore: React.PropTypes.bool.isRequired,
        allowsShare: React.PropTypes.bool.isRequired,
        allowsShortcut: React.PropTypes.bool.isRequired,
        date: React.PropTypes.string.isRequired,
        hasReminder: React.PropTypes.bool.isRequired,
        hasShortcut: React.PropTypes.bool.isRequired,
        inTrash: React.PropTypes.bool.isRequired,
        key: React.PropTypes.string.isRequired,
        presentAvatarUrls: React.PropTypes.arrayOf(React.PropTypes.string).isRequired,
        snippet: React.PropTypes.string,
        thumbnailUrl: React.PropTypes.string,
        title: React.PropTypes.string
      })).isRequired,
      noteViewOptions: React.PropTypes.shape({
        isShowImages: React.PropTypes.bool.isRequired,
        isShowText: React.PropTypes.bool.isRequired
      }),
      notesListDisplayState: React.PropTypes.string.isRequired,
      notesPresenter: React.PropTypes.shape({
        addShortcut: React.PropTypes.func.isRequired,
        clearScroll: React.PropTypes.func.isRequired,
        expunge: React.PropTypes.func.isRequired,
        fetch: React.PropTypes.func.isRequired,
        remove: React.PropTypes.func.isRequired,
        removeShortcut: React.PropTypes.func.isRequired,
        restore: React.PropTypes.func.isRequired,
        select: React.PropTypes.func.isRequired,
        sendByWorkChat: React.PropTypes.func.isRequired,
        setListIndex: React.PropTypes.func.isRequired,
        setNotebookHeaderScrolled: React.PropTypes.func.isRequired,
        setSortOrder: React.PropTypes.func.isRequired,
        showReminderSetDialog: React.PropTypes.func.isRequired,
        toggleShowImages: React.PropTypes.func.isRequired,
        toggleShowText: React.PropTypes.func.isRequired
      }).isRequired,
      numNotesBuffer: React.PropTypes.number.isRequired,
      reminders: React.PropTypes.arrayOf(React.PropTypes.shape({
        formattedReminderTime: React.PropTypes.string,
        guid: React.PropTypes.string.isRequired,
        notebookGuid: React.PropTypes.string.isRequired,
        notebookName: React.PropTypes.string.isRequired,
        reminderDoneTime: React.PropTypes.object, // Date
        reminderOrder: React.PropTypes.number,
        reminderTime: React.PropTypes.object, // Date
        title: React.PropTypes.string.isRequired
      })).isRequired,
      remindersListCollapsedState: React.PropTypes.object,
      remindersListHeight: React.PropTypes.number,
      scrollToIndex: React.PropTypes.number,
      selectedNoteGuid: React.PropTypes.string,
      selectedNotebookGuid: React.PropTypes.string,
      totalNotes: React.PropTypes.number.isRequired,
      windowHeight: React.PropTypes.number
    },

    getDefaultProps: function getDefaultProps() {
      return {
        noteViewOptions: {
          isShowText: true,
          isShowImages: true
        },
        numNotesBuffer: 5,
        remindersListCollapsedState: {},
        remindersListHeight: REMINDERS_COLLAPSED_HEIGHT,
        scrollToIndex: null,
        bannerType: BANNER_TYPES.NONE
      };
    },

    getInitialState: function getInitialState() {
      return {
        fleChecklistHeight: 0,
        bobFleChecklistHeight: 0,
        headerScrolled: false,
        scrollWindowHeight: 100,
        showFleChecklist: false,
        showBobFleChecklist: false,
        showCommEngineCard: false
      };
    },

    componentDidMount: function componentDidMount() {
      this.findScrollWindowHeight();
    },

    componentWillReceiveProps: function componentWillReceiveProps(nextProps) {
      var scrollArea = ReactDOM.findDOMNode(this.refs.scrollArea);
      if (this.props.selectedNotebookGuid !== nextProps.selectedNotebookGuid || this.props.notesListDisplayState !== nextProps.notesListDisplayState || this.props.isBusiness !== nextProps.isBusiness) {
        if (scrollArea) {
          // Changing Context - scroll to top.
          scrollArea.scrollTop = 0;
        }
        this.findScrollWindowHeight(nextProps, false);
        this.props.notesPresenter.setNotebookHeaderScrolled(false);
      }
      if (this.props.windowHeight !== nextProps.windowHeight || this.props.bannerType !== nextProps.bannerType) {
        this.findScrollWindowHeight(nextProps);
      }

      var showFleChecklist = nextProps.notesListDisplayState === 'ALL_NOTES' && !!nextProps.fleChecklistData;

      var showBobFleChecklist = nextProps.notesListDisplayState === 'ALL_NOTES' && !!nextProps.bobFleChecklistData;

      var showCommEngineCard = nextProps.notesListDisplayState === 'ALL_NOTES' && !!nextProps.commEngineCardData;
      this.setState({ showBobFleChecklist: showBobFleChecklist, showFleChecklist: showFleChecklist, showCommEngineCard: showCommEngineCard });
    },

    shouldComponentUpdate: function shouldComponentUpdate(nextProps, nextState) {
      return this.props.fleChecklistData !== nextProps.fleChecklistData || this.props.bobFleChecklistData !== nextProps.bobFleChecklistData || this.props.commEngineCardData !== nextProps.commEngineCardData || this.props.noteInfo !== nextProps.noteInfo || this.props.noteViewOptions !== nextProps.noteViewOptions || this.props.notesListDisplayState !== nextProps.notesListDisplayState || this.props.reminders !== nextProps.reminders || this.props.remindersListHeight !== nextProps.remindersListHeight || this.props.remindersListCollapsedState !== nextProps.remindersListCollapsedState || this.props.scrollToIndex !== null || this.props.selectedNoteGuid !== nextProps.selectedNoteGuid || this.props.selectedNotebookGuid !== nextProps.selectedNotebookGuid || this.props.totalNotes !== nextProps.totalNotes || this.props.windowHeight !== nextProps.windowHeight || this.state.fleChecklistHeight !== nextState.fleChecklistHeight || this.state.bobFleChecklistHeight !== nextState.bobFleChecklistHeight || this.state.headerScrolled !== nextState.headerScrolled || this.state.scrollWindowHeight !== nextState.scrollWindowHeight;
    },

    componentDidUpdate: function componentDidUpdate() {
      if (this.props.scrollToIndex !== null) {
        var scrollArea = ReactDOM.findDOMNode(this.refs.scrollArea);
        if (scrollArea && scrollArea.scrollTop >= this.props.remindersListHeight) {
          var scrollTo = this.props.scrollToIndex * this.getNoteHeight() + this.props.remindersListHeight + this.scrollOffset;
          scrollArea.scrollTop = scrollTo;
        }
        this.props.notesPresenter.clearScroll();
      }
    },

    findScrollWindowHeight: function findScrollWindowHeight(props, headerScrolled) {
      var isHeaderScrolled = headerScrolled || this.state.headerScrolled;
      props = props || this.props;
      var headerHeight;
      var bannerHeight;
      switch (props.notesListDisplayState) {
        case 'NOTEBOOK':
        case 'TRASH':
          headerHeight = isHeaderScrolled ? HEADER_HEIGHTS.SINGLE_NOTEBOOK_HEADER_COLLAPSED : HEADER_HEIGHTS.SINGLE_NOTEBOOK_HEADER_EXPANDED;
          break;
        case 'SEARCH':
          headerHeight = HEADER_HEIGHTS.SEARCH;
          break;
        case 'TAG':
          headerHeight = HEADER_HEIGHTS.TAG;
          break;
        case 'ALL_NOTES':
        default:
          headerHeight = HEADER_HEIGHTS.ALL_NOTES;
      }
      switch (props.bannerType) {
        case BANNER_TYPES.NORTH:
        case BANNER_TYPES.SOUTH:
          bannerHeight = BANNER_HEIGHT;
          break;
        case BANNER_TYPES.TINY:
          bannerHeight = BANNER_HEIGHT_TINY;
          break;
        default:
          bannerHeight = 0;
      }
      var newState = { scrollWindowHeight: props.windowHeight - headerHeight - bannerHeight };
      if (headerScrolled !== undefined) {
        newState.headerScrolled = headerScrolled;
      }
      this.setState(newState);
    },

    scrollOffset: 0,

    getNoteHeight: function getNoteHeight(props) {
      props = props || this.props;
      if (!props.noteViewOptions.isShowText && !props.noteViewOptions.isShowImages) {
        return NOTE_HEIGHTS.NO_IMAGES_OR_TEXT;
      }
      if (!props.noteViewOptions.isShowImages) {
        return NOTE_HEIGHTS.NO_IMAGES;
      }
      return NOTE_HEIGHTS.FULL_HEIGHT;
    },

    /**
     * Maybe expand or collapse the single notebook header depending on scroll position.
     */
    scrollHeaderMaybe: function scrollHeaderMaybe(elem) {
      var scrollTop = elem.scrollTop;
      if (this.props.notesListDisplayState === 'TRASH' || this.props.notesListDisplayState === 'NOTEBOOK') {
        if (!this.state.headerScrolled && scrollTop > MIN_HEADER_SCROLL.DOWN) {
          this.props.notesPresenter.setNotebookHeaderScrolled(true);
          this.findScrollWindowHeight(null, true);
        } else if (this.state.headerScrolled && scrollTop < MIN_HEADER_SCROLL.UP) {
          this.props.notesPresenter.setNotebookHeaderScrolled(false);
          this.findScrollWindowHeight(null, false);
        }
      }
    },

    fetchMaybe: function fetchMaybe(elem) {
      var fetch = false;
      var noteHeight = this.getNoteHeight();
      var numNotesInWindow = Math.ceil(this.state.scrollWindowHeight / noteHeight);
      var topNoteIndex = Math.ceil((elem.scrollTop - this.props.remindersListHeight) / noteHeight);
      this.scrollOffset = elem.scrollTop - topNoteIndex * noteHeight - this.props.remindersListHeight;
      this.props.notesPresenter.setListIndex(topNoteIndex);
      var lowerLimit = Math.max(topNoteIndex - this.props.numNotesBuffer, 0);
      var upperLimit = Math.min(topNoteIndex + numNotesInWindow + this.props.numNotesBuffer, this.props.totalNotes);
      for (var i = lowerLimit; i < upperLimit; i++) {
        if (!this.props.noteInfo[i]) {
          fetch = Math.max(i - this.props.numNotesBuffer, 0);
          break;
        }
      }
      if (fetch >= 0 && fetch !== false) {
        var numNotesToFetch = numNotesInWindow + 2 * this.props.numNotesBuffer;
        this.props.notesPresenter.fetch(fetch, numNotesToFetch);
      }
    },

    showReminders: function showReminders() {
      return this.props.reminders && this.props.reminders.length && (this.props.notesListDisplayState === 'ALL_NOTES' || this.props.notesListDisplayState === 'NOTEBOOK');
    },

    render: function render() {
      var _this = this;

      var content = [];

      if (this.state.showFleChecklist) {
        content.push(React.createElement(FleChecklist, _extends({
          key: 'fleChecklist',
          onHeightUpdated: function onHeightUpdated(fleChecklistHeight) {
            return _this.setState({ fleChecklistHeight: fleChecklistHeight });
          }
        }, this.props.fleChecklistData)));
      }

      if (this.state.showBobFleChecklist) {
        content.push(React.createElement(BobFleChecklist, _extends({
          key: 'bobFleChecklist',
          onHeightUpdated: function onHeightUpdated(bobFleChecklistHeight) {
            return _this.setState({ bobFleChecklistHeight: bobFleChecklistHeight });
          }
        }, this.props.bobFleChecklistData)));
      }

      if (this.showReminders()) {
        content.push(React.createElement(RemindersList, _extends({
          key: 'remindersList'
        }, this.props, {
          expanded: this.props.remindersListCollapsedState.TOP_LEVEL
        })));
      }
      if (this.state.showCommEngineCard) {
        content.push(React.createElement(CommEngineCard, _extends({
          key: 'commEngineCard'
        }, this.props.commEngineCardData)));
      }
      var noteHeight = this.getNoteHeight();
      var heights = [];
      if (this.showReminders()) {
        heights.push(this.props.remindersListHeight);
      }
      if (this.state.showFleChecklist) {
        heights.push(this.state.fleChecklistHeight);
      }

      if (this.state.showBobFleChecklist) {
        heights.push(this.state.bobFleChecklistHeight);
      }

      if (this.state.showCommEngineCard) {
        heights.push(this.props.commEngineCardData.height);
      }
      var placeholderNote;
      for (var i = 0; i < this.props.totalNotes; i++) {
        var info = this.props.noteInfo[i] || {};

        var isShowDivider = i !== 0;
        heights.push(noteHeight);

        var note;
        if (placeholderNote && !info.key) {
          /* Optimization: only construct a single "Loading..." placeholder note, and
           * reference this note in each NoteListItem that shows a placeholder. Creating
           * over 10000 notes is slow, even just in JS without touching the DOM. */
          note = placeholderNote;
        } else {
          note = React.createElement(Note, {
            index: i,
            addShortcut: this.props.notesPresenter.addShortcut,
            allowsDelete: info.allowsDelete,
            allowsExpunge: info.allowsExpunge,
            allowsReminder: info.allowsReminder,
            allowsRestore: info.allowsRestore,
            allowsShare: info.allowsShare,
            allowsShortcut: info.allowsShortcut,
            date: info.date,
            expunge: this.props.notesPresenter.expunge,
            guid: info.key,
            hasReminder: info.hasReminder,
            hasShortcut: info.hasShortcut,
            inTrash: info.inTrash,
            isShowImages: this.props.noteViewOptions.isShowImages,
            isShowText: this.props.noteViewOptions.isShowText,
            isTransitionDisabled: i < this.props.scrollToIndex,
            presentAvatarUrls: info.presentAvatarUrls,
            remove: this.props.notesPresenter.remove,
            removeShortcut: this.props.notesPresenter.removeShortcut,
            restore: this.props.notesPresenter.restore,
            select: this.props.notesPresenter.select,
            selected: info.key === this.props.selectedNoteGuid,
            sendByWorkChat: this.props.notesPresenter.sendByWorkChat,
            isShowDivider: isShowDivider,
            showReminderSetDialog: this.props.notesPresenter.showReminderSetDialog,
            snippet: info.snippet,
            thumbnailUrl: info.thumbnailUrl,
            title: info.title
          });

          if (!placeholderNote && !info.key && i > 0) {
            /* If this is the first placeholder note, save it for future use. Don't save
             * the first note element because its `isShowDivider` will be different from
             * the rest. */
            placeholderNote = note;
          }
        }

        content.push(React.createElement(
          NoteListItem,
          { key: i },
          note
        ));
      }

      // Only show the "how to create a new note" help illustration if no checklist.
      if (!this.state.showFleChecklist && !this.state.showBobFleChecklist) {
        content.push(React.createElement(EmptyState, _extends({ key: 'emptyState' }, this.props)));
        heights.push(339); // magic number - coordinate with EmptyState styles
      }

      var fetchFn = _.throttle(_.debounce(this.fetchMaybe, SCROLL_DELAY), SCROLL_DELAY / 2);
      var checkHeaderFn = this.props.notesListDisplayState === 'NOTEBOOK' || this.props.notesListDisplayState === 'TRASH' ? _.throttle(this.scrollHeaderMaybe, SCROLL_DELAY / 2) : _.noop;
      var scrollFn = function scrollFn(elem) {
        fetchFn(elem);
        checkHeaderFn(elem);
      };

      return React.createElement(
        Infinite,
        {
          ref: 'scrollArea',
          className: BASE_NAME,
          handleScroll: scrollFn,
          timeScrollStateLastForAfterUserScrolls: 0,
          containerHeight: this.state.scrollWindowHeight,
          elementHeight: heights
        },
        content
      );
    }
  });

  return ScrollWindow;
});